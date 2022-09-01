package Thread.Consumer_Producer2;

import java.util.concurrent.BlockingQueue;

class ProducerB implements Runnable {
    volatile BlockingQueue queue;

    ProducerB(BlockingQueue queue, String name) {
        this.queue = queue;
        new Thread(this, name).start();
    }

    public void run() {
        char i = 'a';
        try {
            while (i <= 'z') {
                queue.put(i++);
                System.out.println(Thread.currentThread().getName() + " produces: " + (char)(i - 1));
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupted");
        }
    }
}
