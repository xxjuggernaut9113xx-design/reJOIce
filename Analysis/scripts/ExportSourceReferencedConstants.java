// @category Recovery
import ghidra.app.script.GhidraScript;
import java.nio.file.*;
import java.util.*;
import java.util.regex.*;
public class ExportSourceReferencedConstants extends GhidraScript {
    public void run() throws Exception {
        String[] args=getScriptArgs();
        Matcher matcher=Pattern.compile("(?:DAT|UNK)_([0-9a-fA-F]{9,16})").matcher(Files.readString(Paths.get(args[0])));
        Set<String> addresses=new TreeSet<>();
        while(matcher.find()) addresses.add(matcher.group(1));
        StringBuilder text=new StringBuilder("address\tfloat\tint32\n");
        for(String address:addresses) {
            try { text.append(address).append('\t').append(getFloat(toAddr(address))).append('\t').append(getInt(toAddr(address))).append('\n'); }
            catch(Exception error) { println(address+": "+error.getMessage()); }
        }
        Files.writeString(Paths.get(args[1]),text);
    }
}
