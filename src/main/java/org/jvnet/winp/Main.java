package org.jvnet.winp;

/**
 * Test driver class
 *
 * @author Kohsuke Kawaguchi
 */
public class Main {
    public static void main(String[] args) {
        WinProcess.enableDebugPrivilege();

        if (args[0].equals("list")) {
            for (WinProcess p : WinProcess.all()) {
                print(p);
            }
        } else if (args[0].equals("sleep")) {
            Runtime.getRuntime().addShutdownHook(new Thread() {
                @Override
                public void run() {
                    System.out.println("sleeping for 3 seconds");
                    try {
                        Thread.sleep(3000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println("done sleeping");
                }
            });

            System.out.println("running, going to sleep");

            try {
                Thread.sleep(1000 * 1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else {
            WinProcess p = new WinProcess(Integer.parseInt(args[0]));
            print(p);
            if (args.length>1) {
                if (args[1].equals("kill")) {
                    p.kill(10 * 1000);
                }
                if (args[1].equals("kill-recursive")) {
                    p.killRecursively(10 * 1000);
                }
            }
        }
    }

    private static void print(WinProcess p) {
        System.out.printf("%4d : %s\n", p.getPid(),p.getCommandLine());
        System.out.printf("  %s\n",p.getEnvironmentVariables());
    }
}
