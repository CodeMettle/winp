import org.jvnet.winp.WinProcess;

/**
 * Test program.
 * @author Kohsuke Kawaguchi
 */
public class Main {
    public static void main(String[] args) {
        WinProcess p = new WinProcess(Integer.parseInt(args[0]));
        p.killRecursively(10 * 1000);
        // p.setPriority(Priority.BELOW_NORMAL);
    }
}
