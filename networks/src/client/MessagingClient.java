import java.net.*;
import java.io.*;
import java.util.*;

/*
 * Main class representing the client program
 */
public class MessagingClient
{
    private Socket socket                   = null;
    private ObjectInputStream inputStream   = null;
    private ObjectOutputStream outputStream = null;

    /*
     * @param address
     * @param port
     */
    public MessagingClient(String address, int port)
    {
        try
        {
            this.socket         = new Socket(address, port);
            //for some reason I am not smart enough to understand, changing the order of initialization to first the input Stream and then the output Stream breaks the code....
            this.outputStream   = new ObjectOutputStream(socket.getOutputStream());
            this.inputStream    = new ObjectInputStream(socket.getInputStream());
        }
        catch (IOException e) { System.out.println(e); }
    }
    
    /*
     * Implements the create account function request
     * @param uname
     */
    private void createAccount(String uname)
    {
        //construct packet with function id = 1 and username data
        Packet packet = new Packet(1, new String[] { uname });
        
        try
        {
            //send it
            this.outputStream.writeObject(packet);
            
            try
            {
                //wait response
                Packet resp = (Packet)this.inputStream.readObject();
                //print to user the corresponding message (the auth token, some error message, ..)
                if (resp.fn_id == 0) System.out.println(resp.args[0]);
                else if (resp.fn_id == -1) System.out.println("Invalid Username");
                else if (resp.fn_id == -2) System.out.println("Sorry, the user already exists");
                //else should never happen
            } 
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Implements the show accounts request
     * @param authToken
     */
    private void showAccounts(String authToken)
    {
        Packet packet = new Packet(2, new String[] { authToken });
        
        try
        {
            this.outputStream.writeObject(packet);
            
            try
            {
                Packet resp = (Packet)this.inputStream.readObject();
                //if response == 0 (success) print accounts
                if (resp.fn_id == 0) 
                {
                    for (int i = 0; i < resp.args.length; ++i)
                    {
                        System.out.println(i + ". " + resp.args[i]);
                    }                    
                } //else print error messages
                else if (resp.fn_id == -5) System.out.println("Invalid Auth Token");
            }
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Implements the send message request
     * @param authToken
     * @param recipient
     * @param body
     */
    private void sendMessage(String authToken, String recipient, String body)
    {
        //same as before
        Packet packet = new Packet(3, new String[] { authToken, recipient, body });
        
        try
        {
            this.outputStream.writeObject(packet);
            
            try
            {
                Packet resp = (Packet)this.inputStream.readObject();
                
                if (resp.fn_id == 0) System.out.println("OK");
                else if (resp.fn_id == -1) System.out.println("User does not exist");
                else if (resp.fn_id == -5) System.out.println("Invalid Auth Token");
            }
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Implements the show inbox request
     * @param authToken
     */
    private void showInbox(String authToken)
    {
        Packet packet = new Packet(4, new String[] { authToken });
        
        try
        {
            this.outputStream.writeObject(packet);
            
            try
            {
                Packet resp = (Packet)this.inputStream.readObject();
                
                if (resp.fn_id == 0)
                {
                    for (int i = 0; i < resp.args.length; i += 2)
                    {
                        System.out.println(resp.args[i] + ". from:" + resp.args[i+1]);
                    }
                }
                else if (resp.fn_id == -5) System.out.println("Invalid Auth Token");
            }
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Implements the read message request
     * @param authToken
     * @param msgId The message's id to print
     */
    private void readMessage(String authToken, String msgId)
    {
        Packet packet = new Packet(5, new String[] { authToken, msgId });

        try
        {
            this.outputStream.writeObject(packet);

            try
            {
                Packet resp = (Packet)this.inputStream.readObject();

                if (resp.fn_id == 0) System.out.println("(" + resp.args[0] + ") " + resp.args[1]);
                else if (resp.fn_id == -1) System.out.println("Message ID does not exist");
                else System.out.println("Invalid Auth Token");
            }
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Implements the delete message request
     * @param authToken
     * @param msdId The message's id to delete
     */
    private void deleteMessage(String authToken, String msgId)
    {
        Packet packet = new Packet(6, new String[] { authToken, msgId });

        try
        {
            this.outputStream.writeObject(packet);

            try
            {
                Packet resp = (Packet)this.inputStream.readObject();

                if (resp.fn_id == 0) System.out.println("OK");
                else if (resp.fn_id == -1) System.out.println("Message does not exist");
                else System.out.println("Invalid Auth Token");
            }
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Requests appropriate function
     * @param fn_id The function's id
     * @param args The function's arguments
     */
    public void exec(int fn_id, String[] args)
    {
        switch (fn_id)
        {
        case 1: //create account
            if (args.length != 1) 
            {
                System.out.println("Wrong arguments");
                return;
            }
            this.createAccount(args[0]);
        break;

        case 2: //show accounts
            if (args.length != 1) 
            {
                System.out.println("Wrong arguments");
                return;
            }
            this.showAccounts(args[0]); 
        break;

        case 3: //send msg
            if (args.length < 3) //here arguemnts can be as many since the message can contain spaces
            {
                System.out.println("Wrong arguments");
                return;
            }
            String body = "";
            for (int i = 2; i < args.length; ++i) body += args[i] + " ";
            this.sendMessage(args[0], args[1], body);
        break;

        case 4: //show inbox
            if (args.length != 1) 
            {
                System.out.println("Wrong arguments");
                return;
            }
            this.showInbox(args[0]);
        break;

        case 5: //read msg
            if (args.length != 2) 
            {
                System.out.println("Wrong arguments");
                return;
            }
            this.readMessage(args[0], args[1]);
        break;

        case 6: //delete msg
            if (args.length != 2)
            {
                System.out.println("Wrong arguments");
                return;
            }
            this.deleteMessage(args[0], args[1]);
        break;
        
        default:
            System.out.println("Wrong arguments");
            return;
        }
    }
    
    public static void main(String[] args)
    {
        if (args.length < 3) 
        {
            System.out.println("Wrong arguments");
            return;
        }
        MessagingClient client = new MessagingClient(args[0], Integer.parseInt(args[1]));
        client.exec(Integer.parseInt(args[2]), Arrays.copyOfRange(args, 3, args.length)); //execute command given in args
    }
}
