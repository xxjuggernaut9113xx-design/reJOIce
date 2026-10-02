// @category Codex
import ghidra.app.script.GhidraScript;
import ghidra.program.model.data.TerminatedUnicodeDataType;
import ghidra.program.model.mem.MemoryBlock;
import java.io.*;
public class LoadNativeData extends GhidraScript {
    public void run() throws Exception {
        String[] args=getScriptArgs();
        File data=new File(args[0]);
        if(currentProgram.getMemory().getBlock("OriginalRdata")==null) {
            try(InputStream in=new FileInputStream(data)) {
                MemoryBlock b=currentProgram.getMemory().createInitializedBlock("OriginalRdata",toAddr(Long.parseUnsignedLong(args[1].substring(2),16)),in,data.length(),monitor,false);
                b.setRead(true); b.setWrite(false); b.setExecute(false);
            }
        }
        // Native project constants are narrow and wide strings in this original VA range.
        long start=0x14cf35000L, end=0x14cf80000L;
        for(long at=start;at<end;) {
            int a=getByte(toAddr(at))&255;
            if(a>=32 && a<=126) {
                boolean wide=getByte(toAddr(at+1))==0;
                int count=0; long p=at;
                while(p+1<end && count<1000) {
                    int c=getByte(toAddr(p))&255;
                    if(c<32 || c>126 || (wide && getByte(toAddr(p+1))!=0)) break;
                    count++; p+=wide?2:1;
                }
                if(count>=4 && getByte(toAddr(p))==0 && getDataAt(toAddr(at))==null) {
                    try { if(wide) createData(toAddr(at),TerminatedUnicodeDataType.dataType); else createAsciiString(toAddr(at)); } catch(Exception ignored) {}
                }
                at=Math.max(at+1,p+(wide?2:1));
            } else at++;
        }
        println("Loaded original readonly data for native decompilation");
    }
}
