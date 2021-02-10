/**
 * @author Stergios Moumtzis
 */
public class Quick_Answer_Round extends Round {
    /**
     *
     * @param q indicates the number of questions shown for each round
     */
    public Quick_Answer_Round(int q) {super(q);}

    /**
     * In this game mode, the first player that answers correct in the current question
     * earns 1000 points, while the other earns 500 points.(This game mode works only on multiplayer)
     * @param player Player type array
     * @param current indicates which player is playing at the moment
     * @param choice indicates the player`s answer in the displayed question
     * @param pos the index of the current question
     * @return true if the player answered right in the current question
     */
    @Override
    public boolean play(Player[] player, int current, int choice, int pos) {
        int oldScore = player[current].getScore();
        if (Iquestions[pos].getCorrect() == choice){
            player[current].setScore(oldScore + 1000);
            player[Math.abs(current - 1)].setScore(oldScore + 500);
            return true;
        }
        else{
            return false;
        }

    }
}
