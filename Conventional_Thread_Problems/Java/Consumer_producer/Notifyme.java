package Thread.Consumer_producer;

public class Notifyme {
    public static void main(String[] args) {
        X xx = new X();
        Producer1 producer = new Producer1(xx);
        Consumer1 consumer = new Consumer1(xx);
        producer.thread.start();
        consumer.thread.start();
        try {
            producer.thread.join();
            consumer.thread.join();
        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }
}

