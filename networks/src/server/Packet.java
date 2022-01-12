import java.io.*;

/*
 * Class that represents any data being sent or recieved in the server and client
 * Is serializable
 * Everything is public, since this is basically a C like struct
 */
public class Packet implements java.io.Serializable
{
    //when client sends, fn_id is function id, when server responds it is the response code (0 success, -1 error,  ...)
    public int fn_id;
    public String[] args; //function's arguments, or server's response data

    Packet(int fn_id, String[] args)
    {
        this.fn_id  = fn_id;
        this.args   = args;
    }
}
