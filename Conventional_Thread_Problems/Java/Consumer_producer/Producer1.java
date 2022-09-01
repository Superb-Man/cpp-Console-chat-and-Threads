package Thread.Consumer_producer;

class Producer1 implements Runnable {
    private X x;
    Thread thread;

    Producer1(X x) {
        this.x = x;
        thread = new Thread(this);
    }

    public void run() {
        char i = 'A';
        while (i <= 'Z') {
            x.put(i++);
        }
    }
    /*
    for endless loop
    public void run() {
        char i = 'A';
        while (true) {
            x.put(i++);
            if (i - 1 == 'Z') i = 'A';
        }
    }*/
}
