// @category Codex
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SourceType;
import java.nio.file.*;
public class SeedNativeSymbols extends GhidraScript {
    public void run() throws Exception {
        for(String line:Files.readAllLines(Paths.get(getScriptArgs()[0]))) {
            String[] parts=line.split("\t",2);
            if(parts.length!=2) continue;
            Address at=toAddr(Long.parseUnsignedLong(parts[0].substring(2),16));
            if(!currentProgram.getMemory().contains(at)) continue;
            disassemble(at);
            if(getFunctionAt(at)==null) createFunction(at,null);
            if(getFunctionAt(at)!=null) getFunctionAt(at).setName(parts[1],SourceType.IMPORTED);
        }
        println("Loaded native PDB public function labels");
    }
}
