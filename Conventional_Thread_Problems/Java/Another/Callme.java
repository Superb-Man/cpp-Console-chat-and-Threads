package Thread.Another;

class Callme {
    private String str;

    Callme() {
        str = null;
    }

    public synchronized void call(String str) {
        //System.out.print("["+str) ;
        try {
            System.out.print("[" + str);
            Thread.sleep(1500);
        } catch (InterruptedException e) {
            System.out.println(e);
        }
        System.out.println("]");
    }
}
