// @category Codex
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
public class ExportCalibrationHelpers extends GhidraScript {
 public void run() throws Exception {
  File out=new File(getScriptArgs()[0]);out.mkdirs();
  String[][] selected={{"1481a0db0","AnalyzeCalibrationResults"},{"1481a2200","RegisterBeatTap"},{"1481a2a90","RunManualCalibrationStep"},{"1481a1db0","PlayCalibrationBeat"},{"1481a3160","StartManualCalibration"},{"1481a1420","CompleteManualCalibration"},{"1481a1a50","GetPreciseTime"},{"1481a1910","GetCompensatedTimelineOffset"},{"1481a1b70","GetProfileTotalLatency"},{"1481a1810","GetCalibrationProgress"},{"1481a1ba0","GetRequiredTapsRemaining"},{"1481a1cc0","IsProfileValid"}};
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


