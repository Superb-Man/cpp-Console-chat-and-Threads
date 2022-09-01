package Thread.Another;

class Caller implements Runnable {
    private String str;
    private Thread thread;
    private Callme target;

    Caller(String str, Callme target) {
        this.str = str;
        this.target = target;
        thread = new Thread(this);
    }

    public void run() {
        target.call(str);
    }

    public Thread getThread() {
        return thread;
    }
}
