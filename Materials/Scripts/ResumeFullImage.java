// @category Materials
import ghidra.app.script.GhidraScript;
import java.time.Instant;
import java.nio.file.*;
public class ResumeFullImage extends GhidraScript {
 public void run() throws Exception {
  var options=getCurrentAnalysisOptionsAndValues(currentProgram);
  for(String name:options.keySet()) if(name.equals("PDB Universal")||name.equals("PDB")) setAnalysisOption(currentProgram,name,"false");
  String text="Analysis phase begins at "+Instant.now()+"\nPDB analyzer disabled on this copied project: previous PDB application retained.\nTimeout: 7200 seconds; export is a separate phase.\n";
  Files.writeString(Paths.get(getScriptArgs()[0]),text);
  println(text);
 }
}
