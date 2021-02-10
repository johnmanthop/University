import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class Round_PoolTest {

    @Test
    void getMultiPlayerRounds() {
        Round_Tuple[] round_tuples = Round_Pool.getMultiPlayerRounds(5);
        for(int i = 0; i < 2; i++){
            assertNotNull(round_tuples[i], "Checking if the current object is null");
        }

    }

    @Test
    void getSinglePlayerRounds() {
        Round_Tuple[] round_tuples = Round_Pool.getSinglePlayerRounds(5);
        for(int i = 0; i < 2; i++){
            assertNotNull(round_tuples[i],"Checking if the current object is null");
        }
    }
}