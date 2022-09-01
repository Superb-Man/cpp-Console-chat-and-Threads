package Messenger_Practise;

import java.io.IOException;
import java.util.Scanner;

public class WriteThreadClient implements Runnable {

    private Thread thr;
    private NetworkUtil networkUtil;
    String name;
    boolean isConnected;
    String serverAddress;
    int serverPort;

    public WriteThreadClient(String address, int serverPort, String name) {
        this.isConnected = false;
        this.name = name;
        this.serverAddress = address;
        this.serverPort = serverPort;
        this.thr = new Thread(this);
        thr.start();
    }

    void showOptions(){
        System.out.println("1. Connect\n" + "2. GetList\n" + "3. SendOne\n" + "4. Broadcast");
    }

    public void run() {
        try {
            Scanner input = new Scanner(System.in);
            while (true) {
                showOptions();
                System.out.print("Enter the command number: ");
                int command = input.nextInt();
                input.nextLine();

                if (command == 1){
                    if (isConnected) System.out.println("Client is already connected");
                    else {
                        networkUtil = new NetworkUtil(serverAddress, serverPort);
                        networkUtil.write(name);
                        isConnected = true;
                        new ReadThreadClient(networkUtil);
                    }
                }

                else if (isConnected && command == 2){
                    networkUtil.write(2);
                }
                else if(isConnected && command == 3){
                    String from = name;
                    System.out.print("Enter name of the client to send: ");
                    String to = input.nextLine();
                    System.out.print("Enter the message: ");
                    String text = input.nextLine();
                    networkUtil.write(new Message(from,to,text));
                }
                else if (isConnected && command == 4){
                    String from = name;
                    System.out.print("Enter the message: ");
                    String text = input.nextLine();
                    networkUtil.write(new Message(from,null,text));
                }
                else if (!isConnected) System.out.println("Client needs to connect to the server first");
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



