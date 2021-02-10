import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class Thermometer_RoundTest extends RoundTest{

    @Test
    void play() throws IOException {
        Thermometer_Round round = new Thermometer_Round(1);
        Round.initializeQuestions();
        for(int i = 0; i < player.length; i++){
            player[i] = new Player();
            int r = 0;
            int first_score = 0;
            for(int k = 0; k < round.Iquestions.length; k++) {
                round.Iquestions[k] = Round.Tquestions[k];
                if(round.play(player, i, round.Iquestions[k].getCorrect(), k)){
                    assertEquals(round.c[i], ++r);
                    if(round.c[i] == 5){
                        int sec_score = player[i].getScore();
                        assertEquals(first_score + 5000, sec_score);
                    }
                }
            }
        }
    }
}