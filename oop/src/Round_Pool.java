import java.util.Random;

/**
 * Pool class for round tuples
 * author: Ioannis Manthopoulos
 */
public class Round_Pool {
    static Random generator = new Random();

    /**
     * Generates a tuple array for multiplayer rounds
     * @param n number of rounds to be generated
     * @return array of round tuples
     */
    static Round_Tuple[] getMultiPlayerRounds(int n) {
        Round_Tuple[] rounds = new Round_Tuple[n];
        for (int i = 0; i < rounds.length; ++i) {
            int choice = generator.nextInt(5);
            if (choice == 0) {
                rounds[i] = new Round_Tuple(new Correct_Answer_Round(4), new Correct_Answer_Panel());
            } else if (choice == 1) {
                rounds[i] = new Round_Tuple(new Bet_Round(4), new Bet_Panel());
            } else if (choice == 2) {
                rounds[i] = new Round_Tuple(new Timer_Round(4), new Timer_Panel());
            } else if (choice == 3) {
                rounds[i] = new Round_Tuple(new Thermometer_Round(4), new Thermometer_Panel());
            } else {
                rounds[i] = new Round_Tuple(new Quick_Answer_Round(4), new Quick_Answer_Panel());
            }
        }
        return rounds;
    }

    /**
     * Generates a tuple array for single player rounds (excludes thermometer and quick answer rounds)
     * @param n number of rounds to be generated
     * @return array of round tuples
     */
    static Round_Tuple[] getSinglePlayerRounds(int n) {
        Round_Tuple[] rounds = new Round_Tuple[n];
        for (int i = 0; i < rounds.length; ++i) {
            int choice = generator.nextInt(3);
            if (choice == 0) {
                rounds[i] = new Round_Tuple(new Correct_Answer_Round(2), new Correct_Answer_Panel());
            } else if (choice == 1) {
                rounds[i] = new Round_Tuple(new Bet_Round(2), new Bet_Panel());
            } else {
                rounds[i] = new Round_Tuple(new Timer_Round(2), new Timer_Panel());
            }
        }
        return rounds;
    }
}

