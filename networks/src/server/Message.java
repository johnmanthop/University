/*
 * Class thar represents user's Message
 */
public class Message
{
    private boolean isRead;
    private String sender;
    private String reciever;
    private String body;
    
    /*
     * @param sender
     * @param reciever
     * @param body
     */
    public Message(String sender, String reciever, String body)
    {
        this.isRead     = false;
        this.sender     = sender;
        this.reciever   = reciever;
        this.body       = body;
    }

    public String getSender()      { return this.sender; }
    public String getReciever()    { return this.reciever; }
    public String getBody()        { return this.body; }
    public boolean isRead()        { return this.isRead; }
    
    public void markAsRead()       { this.isRead = true; }
}
