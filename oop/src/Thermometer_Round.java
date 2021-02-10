/**
 * @author Stergios Moumtzis
 */
public class Thermometer_Round extends Round {

    int[] c; //an array used to count the correct answers of each player

    /**
     *
     * @param q indicates the number of questions shown for each round
     */
    public Thermometer_Round(int q) {
        super(q);
        c = new int[2];
        Iquestions = new Text_Question[8];
    }

    /**
     * In this game mode, who ever answers first 5 questions earns 5000 points.
     * Only playable for multiplayer gameplay.
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
            c[current]++;
        }
        if(c[current] == 5){
            player[current].setScore(oldScore + 5000);
        }

        return choice == Iquestions[pos].getCorrect();
    }

    int getC1() { return c[0]; }
    int getC2() { return c[1]; }
}
