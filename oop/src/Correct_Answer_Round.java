/**
 * @author Stergios Moumtzis
 */
public class Correct_Answer_Round extends Round{
    /**
     *
     * @param q indicates the number of questions shown for each round
     */
    public Correct_Answer_Round(int q){super(q);}

    /**
     * According to Correct Answer round, if the player answers right in the displayed question,he will earn 1000 points
     * @param player Player type array
     * @param current indicates which player is playing at the moment
     * @param choice indicates the player`s answer in the displayed question
     * @param pos the index of the current question
     * @return true if the player answered right in the current question
     */

    @Override
    public boolean play(Player[] player, int current, int choice, int pos) {
        if(choice == Iquestions[pos].getCorrect()){
            int oldScore = player[current].getScore();
            player[current].setScore(oldScore+1000);
            return true;
        }
        else{
            return false;
        }
    }
}
