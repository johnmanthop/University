import java.io.*;
import java.net.*;
import java.util.*;

/*
 * Class that acts as the main thread of the server
 */
public class MessagingServer
{
    //accounts list common for all threads (needs synchronization)
    private List<Account> accounts      = null;
    private ServerSocket serverSocket   = null;

    /*
     * @param port The socket's port
     */
    public MessagingServer(int port)
    {
        accounts = new ArrayList<Account>();
        try
        {
            this.serverSocket = new ServerSocket(port);
            System.out.println("Started server");
        }
        catch (IOException e)
        {
            System.out.println(e);
        }
    }
    
    /*
     * Accepts first incoming socket
     */
    private void accept()
    {
        try
        {
            //listen for sockets and create new service thread for each new socket
            Socket clientSocket = this.serverSocket.accept();

            System.out.println("Accepted " + clientSocket.getInetAddress().getHostAddress() + ":" + clientSocket.getPort());
            
            ServiceThread service = new ServiceThread(clientSocket, this.accounts);
            service.start(); 
        }
        catch (IOException e)
        {
            System.out.println(e);
        }
    }

    /*
     * Runs forever and accepts sockets
     */
    public void run()
    {
        //forever accept new sockets
        while (true)
        {
            System.out.println("Waiting for client...");
            this.accept();
            //no need to join since the loop never ends
        }
    }
    
    public static void main(String[] args)
    {
        if (args.length < 1)
        {
            System.out.println("Wrong arguments");
            return;
        }
        MessagingServer server = new MessagingServer(Integer.parseInt(args[0]));
        server.run();
    }
}
