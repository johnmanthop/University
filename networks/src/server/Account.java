import java.util.*;

/*
 * Class that represents user's account
 */
public class Account
{
    //static counter for auth tokens
    private static int acCounter = 0;
    private String username;
    private int authToken;
    private List<Message> messageBox;
    
    /*
     * @param username
     */
    public Account(String username)
    {
        this.username   = username;
        this.authToken  = Account.acCounter++;
        this.messageBox = new ArrayList<Message>();
    }

    public String getUsername()             { return this.username; }
    public int getAuthToken()               { return this.authToken; }

    public void deleteMessage(Message msg)  { this.messageBox.remove(msg); }
    public void addMessage(Message msg)     { this.messageBox.add(msg); }
    /*
     * @param index
     * @return null if index is over the limit, else return pointer to Message object
     */
    public Message getMessage(int index)    { return (index < messageBox.size())?(this.messageBox.get(index)):null; }

    public int getMessageBoxSize()          { return this.messageBox.size(); }
}

