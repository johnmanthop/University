import java.io.*;
import java.net.*;
import java.util.*;

/*
 * Class representing the service provider for a client
 * All writes to the global accounts list are (or should be) synchronized, and some reads as well
 * R/W to input and output streams need not be synchronized, since they are local to the object
 */

public class ServiceThread extends Thread
{
    private Socket clientSocket             = null;
    private ObjectOutputStream outputStream = null;
    private ObjectInputStream inputStream   = null;
    private List<Account> accounts;

    /* @param clientSocket socket pointer created in main thread
     * @param accounts accounts list pointer provided by main thread (should always be locked when accessing)
     */
    public ServiceThread(Socket clientSocket, List<Account> accounts)
    {
        this.accounts = accounts;
        this.clientSocket = clientSocket;
        try
        {
            this.outputStream = new ObjectOutputStream(this.clientSocket.getOutputStream());
            this.inputStream  = new ObjectInputStream (this.clientSocket.getInputStream());
        }
        catch (IOException e) { System.out.println(e); }
    }

    @Override
    public void run()
    {
        this.rec();
    }

    /*
     * Checks if string is valid username, or already exists
     * @param uname The string to check
     * @return 0 on success, -1 on illegal character, -2 on already exists
     */
    private int checkUsername(String uname)
    {
        //check if character is illegal
        for (char ch : uname.toCharArray())
        {
            if (!( Character.isLetterOrDigit(ch) || ch == '_' )) return -1;
        }
        //check if name already exists
        //this part needs to be synchronized so that no 2 accounts with same name are created
        
        synchronized (this.accounts)
        {
            for (Account ac : accounts)
            {
                if (ac.getUsername().equals(uname)) return -2;
            }
        }
        return 0;
    }

    /*
     * Creats and adds account
     * @param uname The account name
     */
    private void createAccount(String uname)
    {
        //check if username is invalid
        int state = this.checkUsername(uname);
        
        Packet packet = null;
        if (state != 0)
        {
            //if it is invalid, construct bad packet
            packet = new Packet(state, null);
        }
        else
        {
            //else construct packet with the auth token created
            Account ac = new Account(uname);
            packet = new Packet(0, new String[] {Integer.toString(ac.getAuthToken())});
            
            synchronized(this.accounts)
            {
                this.accounts.add(ac);
            }
        }

        try
        {
            this.outputStream.writeObject(packet);
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Checks if given auth token is valid
     * @param authToken The token to chekc
     * @return The account corresponding to the token, or null if the token is invalid
     */
    private Account checkAuthToken(int authToken)
    {
        Account account = null;
        //not synchronized to save concurrency time, since in the worst case the client will simply resend the request
        for (Account acc : accounts) 
        {
            //check if auth token exists
            if (acc.getAuthToken() == authToken) account = acc;
        }  
        
        if (account == null)
        {
            //if not construct and send a bad packet to tell client
            Packet packet = new Packet(-5, null);
            try
            {
                this.outputStream.writeObject(packet);
            }
            catch (IOException e) { System.out.println(e); }
            
            return null; //return null to signify error to caller
        }

        return account;
    }

    /*
     * Implements the shwo accounts function of the server
     * @param authToken
     */
    private void showAccounts(int authToken)
    {
        if (this.checkAuthToken(authToken) == null) return; //if auth token is invalid return
        
        String[] accounts_str = new String[accounts.size()];
        
        synchronized(this.accounts)
        {
            //create string list with account names
            for (int i = 0; i < this.accounts.size(); ++i) accounts_str[i] = this.accounts.get(i).getUsername();
        }

        //construct and send packet with data
        Packet packet = new Packet(0, accounts_str);
        try
        {
            this.outputStream.writeObject(packet);
        }
        catch (IOException e) { System.out.println(e); }
    }
    
    /*
     * Implements the send message function of the server
     * @param authToken
     * @param recipient The message's recipient's account name
     * @param body The message
     */
    private void sendMessage(int authToken, String recipient, String body)
    {
        Account senderAcc = this.checkAuthToken(authToken);
        if (senderAcc == null) return;

        boolean recExists = false;
        Account rec = null;
        
        synchronized(this.accounts)
        {
            //check if recipient exists
            for (Account a : this.accounts) 
            {
                if (a.getUsername().equals(recipient)) 
                {
                    recExists = true;
                    rec = a;
                }
            }
        }

        Packet packet = null;
        if (!recExists)
        {
            //if not construct bad packet
            packet = new Packet(-1, null);
        }
        else
        {
            //else construct normal packet and add message to list
            packet = new Packet(0, null);
           
            String sender = null;
            //not synchronized since accounts can never be deleted and usernames are immutable
            sender = senderAcc.getUsername();
            Message msg = new Message(sender, recipient, body);
            //synch the write operation
            synchronized(rec)
            {
                rec.addMessage(msg);
            }
        }
        try
        {
            this.outputStream.writeObject(packet);
        }
        catch (IOException e) { System.out.println(e); }     
    }

    /*
     * Implements the show inbox function of the server
     * @param authToken
     */
    private void showInbox(int authToken)
    {
        Account acc = this.checkAuthToken(authToken);
        if (acc == null) return;

        String[] msgs = null;

        //synch accounts (that contains messages) because there is a chance that a message could be deleted during this process
        synchronized(acc)
        {
            //create list with message ids and senders (and the * character if needed)
            //the ids and senders are saved next to each others like pairs
            msgs = new String[2 * acc.getMessageBoxSize()];
            for (int i = 0, j = 0; i < acc.getMessageBoxSize(); ++i, j += 2)
            {
                Message msg = acc.getMessage(i);
                msgs[j]     = Integer.toString(i);
                msgs[j+1]   = msg.getSender() + ( !msg.isRead() ?"*":"");
            }
        }

        Packet packet = new Packet(0, msgs);
        
        try
        {
            this.outputStream.writeObject(packet);
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Implements the read message function of the server
     * @param authToken
     * @param msgId the message's id (index in messageBox list)
     */
    private void readMessage(int authToken, int msgId)
    {
        Account acc = this.checkAuthToken(authToken);
        if (acc == null) return;

        Packet packet = null;
        Message msg = null;
        //synch since the message could be deleted
        synchronized(acc)
        {
            msg = acc.getMessage(msgId);
        }
        //if msg id does not exist construct bad packet
        if (msg == null)
        {
            packet = new Packet(-1, null);
        }
        else
        {
            //else construct packet with proper data and send it
            packet = new Packet(0, new String[] { msg.getSender(), msg.getBody() });
        
            //synch the write operation
            synchronized(msg)
            {
                msg.markAsRead();
            }
        }

        try
        {
            this.outputStream.writeObject(packet);
        }
        catch (IOException e) { System.out.println(e); }
    }
    
    /*
     * Implements the delete message function of the server
     * @param auhtToken
     * @param msgId The message's id (index in messageBox list)
     */
    private void deleteMessage(int authToken, int msgId)
    {
        //same as before basically
        Account acc = this.checkAuthToken(authToken);
        if (acc == null) return;

        Packet packet = null;
        Message msg = null;
        synchronized(acc)
        {
            msg = acc.getMessage(msgId);
        }
        if (msg == null)
        {
            packet = new Packet(-1, null);
        }
        else
        {
            packet = new Packet(0, null);
            synchronized(acc)
            {
                acc.deleteMessage(msg);
            }
        }

        try
        {
            this.outputStream.writeObject(packet);
        }
        catch (IOException e) { System.out.println(e); }
    }

    /*
     * Executes function with given parameters
     * @param fn_id The function id
     * @param args All possible arguments in a list
     */
    private void exec(int fn_id, String[] args)
    {
        switch (fn_id)
        {
            case 1:
                this.createAccount(args[0]);
            break;
            
            case 2:
                this.showAccounts(Integer.parseInt(args[0]));
            break;
            
            case 3:
                this.sendMessage(Integer.parseInt(args[0]), args[1], args[2]);
            break;

            case 4:
                this.showInbox(Integer.parseInt(args[0]));
            break;

            case 5:
                this.readMessage(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
            break;

            case 6:
                this.deleteMessage(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
            break;
        }
    }
    
    /*
     * Records data from client
     */
    private void rec()
    {
        try
        {
            try
            {
                Packet packet = (Packet)this.inputStream.readObject();
                this.exec(packet.fn_id, packet.args);
            }
            catch (ClassNotFoundException e) { System.out.println(e); }
        }
        catch (IOException e) { System.out.println(e); } 
    }
}
