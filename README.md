# cpp Console Chat
This repository contains networking tasks in C++.
The Socket and ServerSocket headers are implemented.One can use it for purposes.
Or implement in other way.
The TCP_Server_Client program is only for the chat between server and client !
The Messenger Program is for several clients communication through a TCP server.
The number of clients,delete,free,remove all are ignored here/unhandled.

# TCP_Server_Client 1
![Screenshot (285)](https://user-images.githubusercontent.com/72699384/135326426-3dc36750-abc5-4656-a96e-ca3f028181fc.png)

# Console Messenger
![Screenshot (290)](https://user-images.githubusercontent.com/72699384/135326697-1724eada-4689-4dc9-84e7-1bc177beddee.png)

/******after closing one**********/

![Screenshot (291)](https://user-images.githubusercontent.com/72699384/135326909-9a28d7c4-01a5-40de-be15-858d404f95e8.png)

You can run the messenger opening the exe files from debug(ofcourse server at first) and copy the client exe and run it for multiple times without closing the previous. Or you can open solutions from both server and client then run server and run multiple instance of client side.

# Server Socket
```
-  create a socket .
-  start server readthread and writethread (If TCP forwarding server , then writethread not much mandatory) .
-  bind to an address - What port am I on ?
-  listen on a port, and wait for a connection to be established.
-  accept the connection from a client.
-  send/recv - to read and write . 
-  shutdown to end read/write.
-  terminate the threads(join) .
-  close to release data .

   For multiple client sockets use " Socket* or list or array of Socket instead of Socket " .

```

# Client Socket
```
-  create a socket 
-  connect to a server .
-  start read and write threads for client side .
-  send/recv - repeat until we have or receive data .
-  shutdown to end read/write .
-  terminate the threads(join) .
-  close to releases data .

```

# Resource
https://docs.microsoft.com/en-us/windows/win32/api/winsock2/

