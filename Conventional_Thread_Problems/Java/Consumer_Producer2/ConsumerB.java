package Thread.Consumer_Producer2;

import java.util.concurrent.BlockingQueue;

class ConsumerB implements Runnable {
    volatile BlockingQueue queue;

    ConsumerB(BlockingQueue queue, String name) {
        this.queue = queue;
        new Thread(this, name).start();
    }

    public void run() {
        try {
            while (!queue.isEmpty()) {
                System.out.println(Thread.currentThread().getName() + " consumes: " + queue.take());
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupted");
        }
    }
}
