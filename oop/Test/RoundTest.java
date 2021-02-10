import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

class RoundTest {
    Player[] player = new Player[2];

    Round round;

    @Test
    void initializeQuestions() throws IOException {
        round = new Bet_Round(1);
        Round.initializeQuestions();
        for(int i = 0; i < Round.Tquestions.length; i++) {
            assertNotNull(Round.Tquestions[i], "Checking if null");
        }
        for(int i = 0; i < Round.IMquestions.length; i++){
            assertNotNull(Round.IMquestions[i], "Checking if null");
        }
    }
}