"""Record byte-offset evidence for normal pace dialogue entry points."""
import ast
import hashlib
import json
from pathlib import Path
from newer_content_contract import PROJECT, SOURCE, require

analysis = PROJECT.parent / "Analysis"
source = (analysis / "trace_difficulty.py").read_text(encoding="utf-8")
node = next(n for n in ast.parse(source).body if isinstance(n, ast.FunctionDef) and n.name == "size")
scope = {}
exec(ast.get_source_segment(source, node), scope)
function = SOURCE / "functions/BP_GlobalManager/ExecuteUbergraph_BP_GlobalManager.json"
data = json.loads(function.read_text(encoding="utf-8"))


def calls(value):
    if isinstance(value, dict):
        yield value.get("StackNode", value.get("VirtualFunctionName", ""))
        for item in value.values():
            yield from calls(item)
    elif isinstance(value, list):
        for item in value:
            yield from calls(item)


offset, sites = 0, []
statements = data["statements"]
for index, statement in enumerate(statements):
    if "BuildVoiceLineCandidatesFromContentTags" in set(calls(statement)):
        following = statements[index + 1]
        require("Set Dialogue and Play Voiceline" in set(calls(following)), "Source normal dialogue control flow changed")
        sites.append({"candidate_builder_offset": offset, "play_offset": offset + scope["size"](statement),
                      "adjacent_unconditional_call": True})
    offset += scope["size"](statement)
require(len(sites) == 3, "Expected three normal pace dialogue entry points")
for site, pace in zip(sites, ("slow", "medium", "fast")):
    site["pace"] = pace
functions = [function, SOURCE / "functions/BP_GlobalManager/BuildVoiceLineCandidatesFromContentTags.json",
             SOURCE / "functions/BP_GlobalManager/DoesDialogueLinePassPronounFilter.json",
             SOURCE / "functions/BP_GlobalManager/Set_Dialogue_and_Play_Voiceline.json"]
report = {"source_executed": False, "normal_pace_sites": sites,
          "policy": {"probability_gate": "none between normal pace animation and candidate/play calls",
                     "candidate_weighting": "one random eligible row per matching media tag; uniform choice between resulting candidates",
                     "fallback": "slow/medium/fast category when no tag candidates",
                     "pronouns": {"0": "Male", "1": "Female", "2": "Neutral"},
                     "accepted_row_pronouns": ["matching selected pronoun", "Neutral", "blank"],
                     "sph_filter": "small_penis tag is excluded when SPHEnabled? is false"},
          "source_sha256": {str(p.relative_to(PROJECT.parent)): hashlib.sha256(p.read_bytes()).hexdigest() for p in functions}}
(PROJECT / "RecoveryEvidence/newer-20261017-dialogue-routing-contract.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(sites))
