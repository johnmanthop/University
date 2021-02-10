import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class Quick_Answer_RoundTest extends RoundTest{

    @Test
    void play() throws IOException {
        Round.initializeQuestions();
        round = new Quick_Answer_Round(1);
        round.Iquestions[0] = Round.Tquestions[0];
        int first_score,sec_score;
        for(int i = 0; i < 2; i++){
            player[i] = new Player();
        }
        for(int i = 0; i < 2; i++){
            if(round.play(player, i, round.Iquestions[0].getCorrect(), 0)){
                first_score = player[Math.abs(i - 1)].getScore();
                sec_score = player[i].getScore();
                assertEquals(first_score + 500, sec_score);
            }
            first_score = 0;
            sec_score = 0;
        }



    }
}