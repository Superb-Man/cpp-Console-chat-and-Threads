package Thread.Consumer_producer;

class Consumer1 implements Runnable {
    private X x;
    Thread thread;

    Consumer1(X x) {
        this.x = x;
        thread = new Thread(this);
    }

    public void run() {
        while (true) {
            x.get();
            if(x.get() == 'Z') break ;
        }
    }
    /*
    for endless loop
    public void run() {
        while (true) {
            x.get();
        }
    }*/
}
