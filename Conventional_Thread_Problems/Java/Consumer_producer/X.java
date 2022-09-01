package Thread.Consumer_producer;

class X{
    private char n ;
    public boolean set = false ;
    public synchronized void put(char n) {
        while (set == true){
            try {
                Thread.sleep(200);
                wait();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        //System.out.println("Put" +set);
        //System.out.println("Put : "+ n);
        set = true ;
        this.n = n ;
        System.out.println("Toriqe gives char : "+ (char) this.n);
        notifyAll() ;
    }
    public synchronized int get(){
        while(set == false) {
            try {
                Thread.sleep(200);
                wait();
            } catch (InterruptedException e) {
                System.out.println(e);
            }
        }
        //System.out.println(set);
        System.out.println("Lamiya gets char  : "+ (char) n);
        set = false ;
        notifyAll();
        return n;
    }
}
