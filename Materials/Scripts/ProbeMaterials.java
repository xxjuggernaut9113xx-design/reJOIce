// @category Materials
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.*;
import ghidra.program.model.mem.*;
import ghidra.program.model.symbol.*;
import java.nio.file.*;
import java.util.regex.Pattern;
public class ProbeMaterials extends GhidraScript {
 public void run() throws Exception {
  StringBuilder b=new StringBuilder();
  b.append("program\t").append(currentProgram.getName()).append("\n");
  b.append("executable_path\t").append(currentProgram.getExecutablePath()).append("\n");
  b.append("image_base\t").append(currentProgram.getImageBase()).append("\n");
  b.append("functions\t").append(currentProgram.getFunctionManager().getFunctionCount()).append("\n");
  b.append("instructions\t").append(currentProgram.getListing().getNumInstructions()).append("\n");
  for(MemoryBlock block:currentProgram.getMemory().getBlocks()) b.append("block\t").append(block.getName()).append("\t").append(block.getStart()).append("\t").append(block.getSize()).append("\n");
  Pattern target=Pattern.compile("UCHPackManager|UFileImportManager|UCHPackStoreController|UMediaPlaybackController|UProgressionManager|UPreciseBeatWidget|UBeatSpawnerManager|ULatencyCompensationManager|UHandyManager|UAdultToyManager|UFFmpegManager|FCHPackManifest|FCHPackMediaEntry",Pattern.CASE_INSENSITIVE);
  int matched=0,eligible=0;
  SymbolIterator symbols=currentProgram.getSymbolTable().getAllSymbols(true);
  while(symbols.hasNext()) {
   Symbol symbol=symbols.next(); String name=symbol.getName(true);
   if(!target.matcher(name).find()) continue;
   matched++; Function f=getFunctionAt(symbol.getAddress());
   if(f==null||f.isExternal()||name.contains("exec")||name.contains("Z_Construct")||name.contains("TCppStructOps")||name.contains("dtor$")||name.contains("scalar deleting")||name.contains("::Static")||name.contains("?Static")||name.contains("?GetPrivateStatic")||name.contains("?FOn")) continue;
   eligible++;
  }
  b.append("target_matching_symbols\t").append(matched).append("\n");
  b.append("target_eligible_functions\t").append(eligible).append("\n");
  var options=currentProgram.getOptions("Program Information");
  for(String key:options.getOptionNames()) if(key.toLowerCase().contains("pdb")||key.toLowerCase().contains("analy")) b.append("metadata\t").append(key).append("\t").append(options.getObject(key,null)).append("\n");
  Files.writeString(Paths.get(getScriptArgs()[0]),b.toString());
  println("MATERIALS_READABILITY_PASS "+currentProgram.getName()+" functions="+currentProgram.getFunctionManager().getFunctionCount());
 }
}
