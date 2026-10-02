// @category Codex
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.regex.Pattern;
public class ExportIntegration extends GhidraScript {
    public void run() throws Exception {
        File out = new File(getScriptArgs()[0]); out.mkdirs();
        Pattern target = Pattern.compile("UCHPackManager|UFileImportManager|UCHPackStoreController|UMediaPlaybackController|UProgressionManager|UPreciseBeatWidget|UBeatSpawnerManager|ULatencyCompensationManager|UHandyManager|UAdultToyManager|UFFmpegManager|FCHPackManifest|FCHPackMediaEntry",Pattern.CASE_INSENSITIVE);
        DecompInterface dec = new DecompInterface();
        try (PrintWriter symbols = writer(new File(out,"integration-symbols.tsv")); PrintWriter code = writer(new File(out,"integration-decompiled.c")); PrintWriter strings=writer(new File(out,"integration-strings.tsv"))) {
            symbols.println("address\tname\ttype");
            SymbolIterator syms=currentProgram.getSymbolTable().getAllSymbols(true);
            int count=0;
            dec.openProgram(currentProgram);
            while(syms.hasNext() && !monitor.isCancelled()) {
                Symbol s=syms.next(); String name=s.getName(true);
                if(!target.matcher(name).find()) continue;
                symbols.println(s.getAddress()+"\t"+name+"\t"+s.getSymbolType());
                Function f=getFunctionAt(s.getAddress());
                if(f==null || f.isExternal() || count>=400 || name.contains("exec") || name.contains("Z_Construct") || name.contains("TCppStructOps") || name.contains("dtor$") || name.contains("scalar deleting") || name.contains("::Static") || name.contains("?Static") || name.contains("?GetPrivateStatic") || name.contains("?FOn")) continue;
                count++;
                DecompileResults r=dec.decompileFunction(f,20,monitor);
                code.println("\n/* "+s.getAddress()+" "+name+" */");
                if(r.decompileCompleted() && r.getDecompiledFunction()!=null) code.println(r.getDecompiledFunction().getC());
                else code.println("/* "+r.getErrorMessage()+" */");
            }
            DataIterator it=currentProgram.getListing().getDefinedData(true);
            while(it.hasNext() && !monitor.isCancelled()) { Data d=it.next(); if(d.hasStringValue() && target.matcher(String.valueOf(d.getValue())).find()) strings.println(d.getAddress()+"\t"+d.getValue()); }
            println("Exported "+count+" targeted decompilations to "+out);
        } finally { dec.dispose(); }
    }
    private PrintWriter writer(File f) throws IOException { return new PrintWriter(new OutputStreamWriter(new FileOutputStream(f),StandardCharsets.UTF_8)); }
}
