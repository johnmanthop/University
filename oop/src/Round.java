import java.io.IOException;
import java.util.*;

/**
 * Abstract class representing the functionality of each round
 * @author Stergios Moumtzis
 */

abstract class Round {

    static int counter1 = 0;
    static int counter2 = 0;

    static int max_text_questions = 12;
    static int max_image_questions =  3;

    public static Question[] Tquestions; //Array used to store texting questions

    public static Question[] IMquestions; //Array used to store image questions

    public Question[] Iquestions; //Array used to store the questions(both image and text questions) for each round

    final int QuestionsPerRound;

    static List<Integer> order_of_display_text = new ArrayList<>(); //List contained with numbers(1 to max_text_questions) used in GetNextRandom for displaying issues
    static List<Integer> order_of_display_image = new ArrayList<>();//List contained with numbers(1 to max_image_questions) used in GetNextRandom for displaying issues

    /**
     *
     * @param q indicates the number of questions shown for each round
     */
    public Round(int q) {
        QuestionsPerRound = q;
        Iquestions = new Text_Question[QuestionsPerRound];
    }

    /**
     * Initializes static question arrays from file
     * @throws IOException in case the file is missing
     */
     public static void initializeQuestions() throws IOException {
         File_Manager fileForText = new File_Manager("Questions");
         File_Manager fileForImage = new File_Manager("IM_Questions");
         String[] temp;
         Tquestions = new Text_Question[max_text_questions];
         IMquestions = new Image_Question[max_image_questions];

         int k = 0;
         int l = 0;
         int c = 0;
         while ((temp = fileForText.ReadAndSplitFromFile("_")) != null) {
             Tquestions[k++] = new Text_Question(
                     temp[0],
                     temp[1],
                     temp[2],
                     temp[3],
                     temp[4],
                     temp[5],
                     Integer.parseInt(temp[6]));
         }
         while ((temp = fileForImage.ReadAndSplitFromFile("_")) != null) {
             IMquestions[c++] = new Image_Question(
                     temp[0],
                     temp[1],
                     temp[2],
                     temp[3],
                     temp[4],
                     temp[5],
                     Integer.parseInt(temp[6]),
                     "Pics/pic" + (++l) + ".jpg");
         }
         for (int i = 0; i < max_text_questions; ++i) {
             order_of_display_text.add(i, i);
         }
         for (int i = 0; i < max_image_questions; ++i) {
             order_of_display_image.add(i, i);
         }
         Collections.shuffle(order_of_display_text);
         Collections.shuffle(order_of_display_image);
     }

    /**
     * This function works as a Question generator
     * @return a random question
     */
     static Question getNextRandom() {
        Random generator = new Random();
        int ch = (generator).nextInt(2); //generating a random number(0 or 1)
        Question tor;
        if (ch == 0) {
            //in this case, the function tries to return a text question if there are any remains.
            //Otherwise, return an image question or null if both counters have been maximized
            if (counter1 < max_text_questions) { tor = Tquestions[order_of_display_text.get(counter1++)]; }
            else if (counter2 < max_image_questions) { tor = IMquestions[order_of_display_image.get(counter2++)]; }
            else { tor = null; }
        } else {
            //in this case, the function tries to return an image question if there are any remains.
            //Otherwise, the function returns a text question or null if both counters have been maximized.
            if  (counter2 < max_image_questions) { tor = IMquestions[order_of_display_image.get(counter2++)]; }
            else if (counter1 < max_text_questions) { tor = Tquestions[order_of_display_text.get(counter1++)]; }
            else { tor = null; }
        }
        return tor;
     }

     abstract boolean play(Player[] player, int current, int choice, int pos);
}