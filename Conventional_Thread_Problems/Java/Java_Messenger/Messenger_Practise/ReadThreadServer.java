package Messenger_Practise;

import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class ReadThreadServer implements Runnable {
    private Thread thr;
    private NetworkUtil networkUtil;
    public HashMap<String, NetworkUtil> clientMap;


    public ReadThreadServer(HashMap<String, NetworkUtil> map, NetworkUtil networkUtil) {
        this.clientMap = map;
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
                    String to = obj.getTo();
                    if(to == null){
                        for (NetworkUtil nu : clientMap.values()){
                            if(nu!=networkUtil) nu.write(obj);
                        }
                    }
                    else{
                        NetworkUtil nu = clientMap.get(to) ;
                        if (nu != null) nu.write(obj) ;
                    }
                }
                else {
                    List<String> clientList = new ArrayList<String>(clientMap.keySet());
                    networkUtil.write(clientList);
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



