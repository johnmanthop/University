/**
 * @author Stergios Moumtzis
 */
public class Timer_Round extends Round {

    /**
     *
     * @param q indicates the number of questions shown for each round
     */
    public Timer_Round(int q) {super(q);}

    /**
     * in this game mode, when a question is displayed there's a timer that counts down to 5
     * seconds and each player who answers correctly earns as many points as the
     * millisecond that still remained when answered multiplied by 0.2.
     * @param player Player type array
     * @param current indicates which player is playing at the moment
     * @param choice indicates the player`s answer in the displayed question
     * @param pos the index of the current question
     * @return true if the player answered right in the current question
     */
    @Override
    public boolean play(Player[] player, int current, int choice, int pos) {
        int rem = player[current].getRemainder();
        int oldScore = player[current].getScore();
        if (Iquestions[pos].getCorrect() == choice){
            player[current].setScore((int) (rem * 0.2) + oldScore);
            return true;
        }
        else{
            return false;
        }
    }
}
