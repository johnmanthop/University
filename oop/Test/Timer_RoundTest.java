import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class Timer_RoundTest extends RoundTest{

    @Test
    void play() throws IOException {
        Round.initializeQuestions();
        round = new Timer_Round(1);
        for(int i = 0; i < 2; i++){
            player[i] = new Player();
        }
        round.Iquestions[0] = Round.Tquestions[0];
        for(int i = 0; i < 2; i++){
            player[i].setRemainder(1000); //random insertion of remainder
            int first_score = player[i].getScore();
            if (round.play(player, i, round.Iquestions[0].getCorrect(), 0)){
                int sec_score = player[i].getScore();
                assertEquals( first_score + (player[i].getRemainder() * 0.2), sec_score);
            }
        }
    }
}