package Thread.Another;

public class Sync{
    public static void main( String []args ){
        Callme C = new Callme() ;
        Caller C1 = new Caller("Heart", C) ;
        Caller C2 = new Caller("Break", C) ;
        Caller C3 = new Caller("Kid", C) ;
        Thread t = new Thread(new Caller("Covid-19,stay home,stay safe",C)) ;
        //t.setPriority(1);
        //System.out.println(t.getPriority()) ;
        t.start() ;
        C1.getThread().start() ;
        C2.getThread().start() ;
        C3.getThread().start() ;
        try{
            C1.getThread().join();
            C2.getThread().join();
            C3.getThread().join();
            t.join();
        }catch (InterruptedException e){
            System.out.println(e);
        }
    }
}
