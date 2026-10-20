import json
import unittest
from newer_content_contract import SOURCE, COUNTS, load_source, validate, required_artwork, all_artwork, canonical, table_rows


class NewerContentContractTests(unittest.TestCase):
    def setUp(self):
        self.catalog = json.loads((SOURCE / "normalized-content-catalog.json").read_text(encoding="utf-8"))
        self.raw = json.loads((SOURCE / "table-values.json").read_text(encoding="utf-8"))

    def test_source_catalog_exact_counts_and_cross_references(self):
        contract = load_source()
        self.assertEqual({k: len(v) for k, v in contract["tables"].items()}, COUNTS)
        self.assertEqual(len(required_artwork(contract)), 118)
        self.assertEqual(len(contract["sources"]), 2)

    def test_all_fourteen_tables_and_modifier_artwork_are_retained(self):
        contract = load_source()
        self.assertEqual(len(contract["tables"]) + len(contract["supplemental_tables"]), 14)
        self.assertEqual(sum(len(rows) for rows in contract["tables"].values()) + sum(len(rows) for rows in contract["supplemental_tables"].values()), 329)
        self.assertEqual(len(all_artwork(contract)), 146)
        self.assertEqual(len(contract["source_tables"]), 14)

    def test_unknown_metric_rejected(self):
        self.catalog["tables"]["DT_Challenges"][0]["Requirements"][0]["MetricType"] = "EMetricType::Unknown"
        with self.assertRaisesRegex(ValueError, "Unknown metric"):
            validate(self.catalog, self.raw)

    def test_unverified_table_rejected(self):
        next(t for t in self.raw["tables"] if t["table"] == "DT_Challenges")["byte_identical_roundtrip"] = False
        with self.assertRaisesRegex(ValueError, "Missing byte-identical source proof"):
            validate(self.catalog, self.raw)

    def test_duplicate_identifier_rejected(self):
        rows = self.catalog["tables"]["DT_PlayerCards"]
        rows[1]["CardID"] = rows[0]["CardID"]
        with self.assertRaisesRegex(ValueError, "Duplicate DT_PlayerCards identifiers"):
            validate(self.catalog, self.raw)

    def test_dangling_card_unlock_rejected(self):
        self.catalog["tables"]["DT_PlayerCards"][0]["RequiredChallengeID"] = "missing"
        with self.assertRaisesRegex(ValueError, "Unknown card challenge"):
            validate(self.catalog, self.raw)

    def test_nested_nulls_match_unreal_empty_names(self):
        rows = table_rows([{"row": "A", "Rewards": [{"ItemIdentifier": None}]}])
        self.assertEqual(rows, [{"Name": "A", "Rewards": [{"ItemIdentifier": ""}]}])
        self.assertEqual(canonical(rows), [{"name": "A", "rewards": [{"itemidentifier": ""}]}])


if __name__ == "__main__":
    unittest.main()
