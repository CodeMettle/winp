import org.jvnet.winp.WinProcess;

import java.io.InputStream;
import java.io.PrintStream;

/**
 * @author Kohsuke Kawaguchi
 */
public class Main2 {
    public static class StreamThread extends Thread {
        private final InputStream is;
        private final PrintStream os;
        private final byte[] buffer = new byte[32 * 1024];

        public StreamThread(InputStream is, PrintStream os) {
            setDaemon(true);
            this.is = is;
            this.os = os;
        }

        @Override
        public void run() {
            while (true) {
                try {
                    int read = is.read(buffer);
                    if (read > 0)
                        os.write(buffer, 0, read);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    public static void doit() throws Exception {
        ProcessBuilder pb = new ProcessBuilder("java",
                "-jar",
                "c:/users/progo/dev/winp/target/winp-1.25-SNAPSHOT.jar",
                "sleep");
/*
        ProcessBuilder pb = new ProcessBuilder("notepad");
*/
        Process p = pb.start();
        new StreamThread(p.getErrorStream(), System.err).start();
        new StreamThread(p.getInputStream(), System.out).start();
        Thread.sleep(3000);
        System.out.println("trying to kill");
        new WinProcess(p).kill(4 * 1000);
        System.out.println("killed");
        p.destroy();
        p.waitFor();
    }

    public static void main(String[] args) throws Exception {
        doit();

        doit();
    }
}
