/**
 * Interface representing the questions` functionality
 * @author Stergios Moumtzis (also for each implementing classes like Text_Question and Image_Question)
 */

public interface Question {
     /**
      * @return a String that indicates the category of the question
      */
     String getCategory();


     /**
      * @return a String that indicates the question itself
      */
     String getQuestion();


     /**
      * @return a table of Strings in which represents the 4 possible answers for the question
      */
     String[] getAnswers();


     /**
      * @return an integer that shows which answer is right(1 or 2 or 3 or 4)
      */
      int getCorrect();

     /**
      *
      * @return a string with the name of the image
      */
      String getSpecial();
}
