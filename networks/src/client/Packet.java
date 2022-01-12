import java.io.*;

//anything being sent or recieved is send or recieved as a Packet object
//make everything public since this is basically a C-like struct
public class Packet implements java.io.Serializable
{
    public int fn_id; //function
    public String[] args; //function's arguments

    Packet(int fn_id, String[] args)
    {
        this.fn_id  = fn_id;
        this.args   = args;
    }
}
