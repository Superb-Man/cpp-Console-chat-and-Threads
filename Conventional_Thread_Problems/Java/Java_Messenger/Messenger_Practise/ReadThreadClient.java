package Messenger_Practise;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ReadThreadClient implements Runnable {
    private Thread thr;
    private NetworkUtil networkUtil;

    public ReadThreadClient(NetworkUtil networkUtil) {
        this.networkUtil = networkUtil;
        this.thr = new Thread(this);
        thr.start();
    }

    public void run() {
        try {
            while (true) {
                Object o = networkUtil.read();
                if (o instanceof Message) {
                    Message obj = (Message) o;
                    if(obj.getTo() != null) {
                        System.out.println("From " + obj.getFrom() + ", To " + obj.getTo() + " : " + obj.getText());
                    }
                    else{
                        System.out.println("Broadcasted from " +obj.getFrom() + ": " + obj.getText());
                    }
                }
                else{
                    List<String> list = (ArrayList<String>) o;
                    System.out.print("Available Clients: ");
                    for (String s : list)
                        System.out.print(s + " , ");
                    System.out.println();
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                networkUtil.closeConnection();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}