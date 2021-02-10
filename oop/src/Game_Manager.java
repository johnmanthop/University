import java.io.IOException;

/** Represents the management class of the project in which important fields and methods are being executed
 * @author Ioannis Manthopoulos
 */
public class Game_Manager {
    Round[] rounds;

    Player[] players;

    GUI_Panel[] round_panels;

    GUI_Frame   main_frame;

    final int round_count;

    static int player_count;
    //Initializing all objects:
    public Game_Manager() throws IOException {
        round_count  = 3;
        player_count = 2;

        rounds  = new Round[round_count];
        players = new Player[player_count];

        round_panels = new GUI_Panel[round_count];

        Round.initializeQuestions();

    /*According to the type of the round(generator = 0 for Correct Answer or generator = 1 for Bet)
     appropriate objects are being initialized (Round and Printer objects)
     */

        for(int i = 0; i < player_count;i++){
            players[i] = new Player();
        }

    }

    /**
     * Function used for the main functionality of the whole game!
     */
    public void start() throws IOException {
        /*Should be put elsewhere*/

        main_frame = new GUI_Frame();

        main_frame.setPlayers(players);

    }
}

