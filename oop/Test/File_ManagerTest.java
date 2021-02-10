import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class File_ManagerTest {

    @Test
    void readAndSplitFromFile() throws IOException {
        File_Manager file1 = new File_Manager("FilesForJUnit/readAndSplitFile_Test");
        String[] words_split;
        while((words_split = file1.ReadAndSplitFromFile("_")) != null){
            assertNotNull(words_split);
        }
    }

    @Test
    void read() throws IOException {
        File_Manager file2 = new File_Manager("FilesForJUnit/read_Test");
        String expected, actual;
        int k = 0;
        actual = file2.read();
        while (actual != null){
            expected = "this is a single line " + (++k);
            assertEquals(expected, actual);
            actual = file2.read();
        }
    }

    @Test
    void writeToFile() throws IOException{
        File_Manager file3 = new File_Manager("FilesForJUnit/WriteTofile_Test");
        file3.WriteToFile("Write a single line");
        String line = file3.read();
        assertEquals(line, "Write a single line");
    }

    @Test
    void increaseByOne() throws IOException{
        File_Manager file4 = new File_Manager("FilesForJUnit/increaseByOne_Test");
        file4.increaseByOne(0);
        file4.reset();
        String line = file4.read();
        assertEquals(1, Character.getNumericValue(line.charAt(14)));

        file4.reset();
        file4.increaseByOne(1);
        file4.reset();
        line = file4.read();
        assertEquals(1, Character.getNumericValue(line.charAt(line.length() - 1)));

        file4.reset();
        file4.WriteToFile("Increase by 1:0 || Increase by 1:0");

    }

    @Test
    void compareAndSwap() throws IOException{
        File_Manager file5 = new File_Manager("FilesForJUnit/compareAndSwap_Test");
        file5.WriteToFile("1000");
        int num1,num2;
        num1 = 500;
        num2 = 1500;

        String line = file5.read();
        assertNotNull(line);
        file5.compareAndSwap(num1);
        file5.reset();

        line = file5.read();
        assertNotNull(line);
        assertNotEquals(line, Integer.toString(num1));
        file5.compareAndSwap(num2);
        file5.reset();

        line = file5.read();
        assertNotNull(line);
        assertEquals(line, Integer.toString(num2));

    }
}