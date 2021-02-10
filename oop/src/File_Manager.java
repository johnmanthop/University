import java.io.*;
import java.util.Scanner;
/**
 * Class representing a file manager with the methods it should provide
 * @author Stergios Moumtzis
 */
public class File_Manager {
    File file;
    Scanner scanner;

    public File_Manager(String filename) throws IOException {
        file = new File(filename);
        scanner = new Scanner(file);
    }

    /**
     * Splits a string according to a prefix
     * @param prefix the prefix character that the string should be split
     * @return an array of the split string
     */
    public String[] ReadAndSplitFromFile(String prefix){
        String line;
        String[] words;
        if (scanner.hasNext()){
            line = scanner.nextLine();
            words = line.split(prefix);
            return words;
        }
        else{
            return null;
        }
    }

    /**
     * reads next line
     * @return the line read, null if scanner is at eof
     */
    public String read(){
        if (scanner.hasNext()){
            return scanner.nextLine();
        }
        else{
            return null;
        }
    }


    /**
     * resets the scanner to the start of the file
     * @throws IOException in case the file is missing
     */
    public void reset() throws IOException {
        scanner = new Scanner(file);
    }

    /**
     * writes string to file
     * @param str string to write
     * @throws IOException in case the file is missing
     */
    public void WriteToFile(String str) throws IOException {
        FileWriter writer = new FileWriter(file);
        writer.write(str);
        writer.close();
    }

    /**
     * Increases the win counter by one
     * @param pos player to increase the win
     * @throws IOException in case the file is missing
     */
    public void increaseByOne(int pos) throws IOException {
        String line = "";
        char score;
        StringBuilder builder;
        if(scanner.hasNext()){
            line = scanner.nextLine();
        }
        builder = new StringBuilder(line);
        if (pos == 1){
            score = line.charAt(line.length() - 1);
            score++;
            builder.setCharAt(line.length() - 1, score);
        }
        else{
            score = line.charAt(14);
            score++;
            builder.setCharAt(14, score);
        }
        line = builder.toString();
        WriteToFile(line);
    }

    /**
     * Swaps highscore, if given highscore is greater than the previous one
     * @param num new highscore
     * @throws IOException in case the file is missing
     */
    public void compareAndSwap(int num) throws IOException {
        reset();
        String temp = scanner.nextLine();
        if (num > Integer.parseInt(temp)){
            WriteToFile(Integer.toString(num));
        }
    }
}
