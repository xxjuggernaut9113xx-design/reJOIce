// @category Recovery
import ghidra.app.script.GhidraScript;
import java.nio.file.*;
public class ExportLootConstants extends GhidraScript {
    public void run() throws Exception {
        String[] addresses={"14bf3cd58","14bf2ebec","14bf56a24","14bf569c8","14bf56a6c","14bfb66c0","14c291cb0","14bf56a80"};
        StringBuilder text=new StringBuilder("address\tfloat\tint32\n");
        for(String address:addresses) text.append(address).append('\t').append(getFloat(toAddr(address))).append('\t').append(getInt(toAddr(address))).append('\n');
        Files.writeString(Paths.get(getScriptArgs()[0]),text);
    }
}
