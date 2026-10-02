// @category Codex
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
public class ExportProgressionHelpers extends GhidraScript {
    public void run() throws Exception {
        File out = new File(getScriptArgs()[0]); out.mkdirs();
        String[][] selected = {{"1481b3090", "ProgressionConstructor"}, {"1481b49f0", "CalculateSessionXP"}, {"1481cc110", "StartNewSession"}, {"1481b6d20", "EndSession"}, {"1481c6a00", "PrepareSessionRewards"}};
        DecompInterface dec = new DecompInterface();
        try (PrintWriter code = new PrintWriter(new OutputStreamWriter(new FileOutputStream(new File(out,"runtime-helpers.c")), StandardCharsets.UTF_8))) {
            for (String[] row : selected) {
                Address at = toAddr(Long.parseUnsignedLong(row[0],16));
                disassemble(at);
                if (getFunctionAt(at) == null) createFunction(at,row[1]);
            }
            dec.openProgram(currentProgram);
            for (String[] row : selected) {
                Address at = toAddr(Long.parseUnsignedLong(row[0],16));
                Function f = getFunctionAt(at);
                code.println("\n/* " + at + " " + row[1] + " */");
                if (f == null) { code.println("/* No function created */"); continue; }
                DecompileResults result = dec.decompileFunction(f,40,monitor);
                if (result.decompileCompleted()) code.println(result.getDecompiledFunction().getC());
                else code.println("/* " + result.getErrorMessage() + " */");
                InstructionIterator it = currentProgram.getListing().getInstructions(f.getBody(),true);
                code.println("/* Instruction evidence:");
                while (it.hasNext()) { Instruction instruction = it.next(); code.println(instruction.getAddress() + " " + instruction); }
                code.println("*/");
            }
        } finally { dec.dispose(); }
    }
}
