/**
 * @author Stergios Moumtzis
 */
public class Bet_Round extends Round{
    /**
     *
     * @param q indicates the number of questions shown for each round
     */
    public Bet_Round(int q) { super(q); }

    /**
     * Used to handle the playing action according to reach round type,
     * this one changes the score according to the bet value saved in the player object
     * @param player Player type array
     * @param current indicates which player is playing at the moment
     * @param choice indicates the player`s answer in the displayed question
     * @param pos the index of the current question
     * @return true if the player answered right in the current question
     */
    @Override
    public boolean play(Player[] player, int current, int choice, int pos) {
        int oldScore = player[current].getScore();

        if(choice == Iquestions[pos].getCorrect()){
            player[current].setScore(oldScore + player[current].getBet());
        } else {
            player[current].setScore(oldScore - player[current].getBet());
        }
        if (player[current].getScore() < 0) player[current].setScore(0);

        return choice == Iquestions[pos].getCorrect();
    }
}
