/**
 * Player class representing one player
 * @author Ioannis Manthopoulos
 */
public class Player {

    int score; //Indicates how many points the player has
    int bet; //Indicates how many points the player will bet according to the displayed question (used in bet panel)
//NOTE:The player must bet 250 or 500 or 750 or 1000 points for each question and it is used only for The BET category
    int rem; //Indicates the player's remaining time (used in timed panels)

    Player() {
        score = 0;
        bet = 0;
    }

    /**
     * score setter
     * @param sc score value to set
     */
    public void setScore(int sc) { this.score = sc; }

    /**
     * score getter
     * @return player score
     */
    public int getScore() { return this.score; }

    /**
     * Sets the player bet for a bet round
     * @param bt player's bet
     */
    public void setBet(int bt) { this.bet = bt; }

    /**
     * Bet getter
     * @return player's bet
     */
    public int getBet() { return this.bet; }

    /**
     * Sets remaining time for a timer round
     * @param rem player's response time
     */
    public void setRemainder(int rem) { this.rem = rem; }

    /**
     * time remainder getter
     * @return player's response time
     */
    public int getRemainder() { return this.rem; }
}
