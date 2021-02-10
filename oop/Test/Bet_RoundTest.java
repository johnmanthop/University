import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class Bet_RoundTest extends RoundTest{

    @Test
    void play() {
        round = new Bet_Round(1);
        player[0] = new Player();

        player[0].setBet(750);
        player[0].setScore(500);

        int first_score = player[0].getScore();
        round.Iquestions = new Question[1];

        round.Iquestions[0] = new Text_Question("Sports",
                "Who is this?","a","b","c","d",1);

        if(round.play(player, 0, round.Iquestions[0].getCorrect(), 0)){
            int sec_score = player[0].getScore();
            assertNotEquals(first_score, sec_score);
        }
        if (!round.play(player,0,round.Iquestions[0].getCorrect() - 1,0)){
            int sec_score = player[0].getScore();
            assertEquals(first_score,sec_score);
        }
    }
}