Readme file for network programming project

The project is split into 2 parts (programs). A server and a client

The server is called like so: java -jar Server.jar <port>
The client is called like so: java -jar Client.jar <ip> (usually localhost) <port> <args...>

-----------------------------------------------------------------------------------------------------
The client program is split into the following:

Packet.java
A class representing the basic packet sent and recieved to and from the server
It contains an integer variable representing either the function id or the server's responce code
And a String array containing all other relevant data.
It implements the serializable interface, so it can be sent through object streams.

MessagingClient.java
The main class of the proram, it contains one method for every function the client needs to send.

------------------------------------------------------------------------------------------------------
The Server program is split into the following:

Packet.java
Same as before

Account.java
A class representing the user's account

Message.java
A class representing the user messages

MessagingServer.java
A class representing the server's main socket. It contains the global accounts list,
and creates a new object of type ServiceThread (look below) that is assigned to a new thread 
each time a new client socket is accepted.

ServiceThread.java
The main object that serves the client's request, it extends the Thread class so it can run concurrently.
The client's socket is passed as an argument from the main thread, and so is the accounts list.
The streams are local to the object, so they need not be synchronized.
It has a method for each possible request from the client.

-------------------------------------------------------------------------------------------------------
The system is created and tested only in a localhost configuration.

Some methods are not synchronized to save time in concurrency, because it is not critical to be synched.
For example the show accounts method is not synched, since the user can simply request again to get the updated list.

The Accounts and Messages objects are created and managed only in the server class, (are not saved in files)
the client only interacts with them with strings provided in packets received from the server.

Ioannis Manthopoulos
12/1/22
