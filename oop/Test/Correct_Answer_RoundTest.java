import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class Correct_Answer_RoundTest extends RoundTest{

    public Correct_Answer_RoundTest() {}

    @Test
    void play() {
        round = new Correct_Answer_Round(1);
        player[0] = new Player();
        player[0].setScore(1000);
        int first_score = player[0].getScore();
        round.Iquestions[0] = new Text_Question("Sports",
        "Who is this?","a","b","c","d",1);
        if(round.play(player, 0, 1, 0)){
            int sec_score = player[0].getScore();
            assertNotEquals(first_score, sec_score);
        }
        if (!round.play(player,0,1,0)){
            int sec_score = player[0].getScore();
            assertEquals(first_score,sec_score);
        }
    }
}