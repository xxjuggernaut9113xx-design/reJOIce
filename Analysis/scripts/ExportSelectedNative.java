// @category Recovery
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.program.model.listing.Function;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

// Import without whole-engine analysis; caller supplies build-specific PDB addresses.
// Exported C remains inferred pseudocode, not original source or runtime evidence.
public class ExportSelectedNative extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("Expected symbols.tsv output-directory");
        Path output = Paths.get(args[1]);
        Files.createDirectories(output);
        DecompInterface decompiler = new DecompInterface();
        if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException(decompiler.getLastMessage());
        List<String> report = new ArrayList<>();
        report.add("address\tname\tstatus\toutput");
        try {
            for (String line : Files.readAllLines(Paths.get(args[0]), StandardCharsets.UTF_8)) {
                monitor.checkCancelled();
                if (line.isBlank() || line.startsWith("#")) continue;
                String[] fields = line.split("\t", 2);
                var address = toAddr(fields[0]);
                String name = fields.length == 2 ? fields[1] : "selected_" + address;
                disassemble(address);
                Function function = getFunctionAt(address);
                if (function == null) function = createFunction(address, null);
                if (function == null) {
                    report.add(fields[0] + "\t" + name + "\tno-function\t");
                    continue;
                }
                function.setComment("Selected newer-build routine; caller-supplied label: " + name);
                var result = decompiler.decompileFunction(function, 45, monitor);
                if (result.decompileCompleted() && result.getDecompiledFunction() != null) {
                    String file = fields[0] + ".c";
                    String text = "// Selected newer-build routine; caller-supplied label: " + name + "\n// Address: " + fields[0]
                        + "\n// Static inferred pseudocode; external calls/types may be unresolved.\n\n"
                        + result.getDecompiledFunction().getC();
                    Files.writeString(output.resolve(file), text, StandardCharsets.UTF_8);
                    report.add(fields[0] + "\t" + name + "\tdecompiled\t" + file);
                } else {
                    report.add(fields[0] + "\t" + name + "\terror\t" + result.getErrorMessage().replace('\n', ' '));
                }
                println("RECOVERY_SELECTED_NATIVE: " + fields[0] + " " + name);
            }
        } finally {
            decompiler.dispose();
            Files.write(output.resolve("selected-native-report.tsv"), report, StandardCharsets.UTF_8);
        }
    }
}
