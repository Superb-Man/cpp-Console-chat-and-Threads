package Thread.Consumer_Producer2;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class PCBlockingQueue {
    public static void main(String[] args) {
        BlockingQueue queue = new ArrayBlockingQueue(1);
        new ProducerB(queue, "Producer");
        new ConsumerB(queue, "Consumer");
        System.out.println("Press Control-C to stop.");
    }
}

