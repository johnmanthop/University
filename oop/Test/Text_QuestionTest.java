import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import java.lang.reflect.Array;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.assertNotEquals;


public class Text_QuestionTest {

    public Text_QuestionTest() {}


    public boolean isEqual(String[] A,String[] B){
        return Arrays.equals(A, B);
    }

    @Test
    public void shuffleTest(){
        String[] answers = {"a", "b", "c", "d"};
        String[] temp;

        Text_Question text_question = new Text_Question("Sports",
                "Who is this?",
                answers[0],
                answers[1],
                answers[2],
                answers[3],
                1);

        temp = text_question.getAnswers();

        Assertions.assertFalse(isEqual(answers, temp), "Checking if shuffle in constructor of the Text_Question class works");
    }
}
