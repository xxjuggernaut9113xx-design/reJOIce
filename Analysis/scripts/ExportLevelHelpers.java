// @category Codex
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
public class ExportLevelHelpers extends GhidraScript {
 public void run() throws Exception {
  File out=new File(getScriptArgs()[0]);out.mkdirs();
  String[][] selected={{"1481b41f0","AddUnlockPoints"},{"1481b4200","AddXP"},{"1481b4f10","CheckLevelUp"},{"1481c32e0","GetXPForNextLevel"},{"1481ca280","ResetProgress"}};
  DecompInterface dec=new DecompInterface();
  try(PrintWriter code=new PrintWriter(new OutputStreamWriter(new FileOutputStream(new File(out,"runtime-helpers.c")),StandardCharsets.UTF_8))) {
   for(String[] row:selected) { Address at=toAddr(Long.parseUnsignedLong(row[0],16));disassemble(at);if(getFunctionAt(at)==null)createFunction(at,row[1]); }
   dec.openProgram(currentProgram);
   for(String[] row:selected) {
    Address at=toAddr(Long.parseUnsignedLong(row[0],16));Function f=getFunctionAt(at);code.println("\n/* "+at+" "+row[1]+" */");
    if(f==null){code.println("/* No function created */");continue;}
    DecompileResults result=dec.decompileFunction(f,40,monitor);
    if(result.decompileCompleted())code.println(result.getDecompiledFunction().getC());else code.println("/* "+result.getErrorMessage()+" */");
    code.println("/* Instruction evidence:");InstructionIterator it=currentProgram.getListing().getInstructions(f.getBody(),true);
    while(it.hasNext()){Instruction instruction=it.next();code.println(instruction.getAddress()+" "+instruction);}code.println("*/");
   }
  } finally {dec.dispose();}
 }
}
