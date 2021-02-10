import javax.swing.*;
import java.awt.*;
import java.io.IOException;

/**
 * Class representing the main gui frame that all panels will be displayed on
 * @author Ioannis Manthopoulos
 */
public class GUI_Frame {
    JFrame frame; //Main jframe
    JPanel card; //Main card panel that all other panels live one
    JPanel start_panel; //Main menu panel
    JPanel end_panel; //End panel
    JLabel score_end_panel; //Label for displaying end scores and stuff...

    GUI_Panel []panels; //Round panel array
    Round     []rounds; //Round logic array
    Player    []players; //Player array

    int current_round; //Signifies the current played round
    int current_question; //Signifies the current played question in the round
    int current_player; //Signifies the current player (0, 1)
    int no_of_players; //Signifies number of palyer
    int round_count; //Signifies how many rounds will be played

    File_Manager wins_m; //File manager for the wins file
    File_Manager hscores_m; //File manager for the highscores file

    GUI_Frame() throws IOException {
        round_count = 3; //3 rounds will be played
        rounds = new Round[round_count];
        panels = new GUI_Panel[round_count];

        frame = new JFrame();
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        frame.setSize(550, 300);
        frame.setVisible(true);

        wins_m = new File_Manager("Wins");
        hscores_m = new File_Manager("Highscore");

        card = new JPanel();
        card.setLayout(new CardLayout());
        frame.add(card);

        start_panel = new JPanel();
        start_panel.setLayout(new BoxLayout(start_panel, BoxLayout.PAGE_AXIS));
        start_panel.add(new JLabel("<html>For single player use a,s,d,f<br />For multiplayer use a,s,d,f on questions that don't play concurrently<br />Or a,s,d,f and u,i,o,p otherwise</html>"));

        //Set start meu buttons
        JButton start_1player = new JButton("1 Player");
        start_1player.addActionListener(actionEvent -> start(1) );

        JButton start_2player = new JButton("2 Players");
        start_2player.addActionListener(actionEvent -> start(2) );

        JButton show_hscore = new JButton("Show single player highscore");
        show_hscore.addActionListener(actionEvent -> {
            try {
                show_hscore_action();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        JButton show_wins = new JButton("Show multi player wins");
        show_wins.addActionListener(actionEvent -> {
            try {
                show_wins_action();
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        score_end_panel = new JLabel();

        end_panel = new JPanel();
        end_panel.setLayout(new FlowLayout());
        end_panel.add(new JLabel("END"));
        end_panel.add(score_end_panel);

        start_panel.add(start_1player);
        start_panel.add(start_2player);
        start_panel.add(show_hscore);
        start_panel.add(show_wins);

        card.add(start_panel, "start");
        card.add(end_panel, "end");

        current_round = 0;
        current_player = 0;
        current_question = 0;

        CardLayout cl = (CardLayout) card.getLayout();
        cl.show(card, "start"); //Display the start panel in the card panel
    }

    /**
     * Show new frame with multiplayer wins
     * @throws IOException exception in case the file is missing or it hasn't been reset
     */
    void show_wins_action() throws IOException {
        //Create a new frame and display the file data
        JFrame local_frame = new JFrame("Wins");
        local_frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        local_frame.setSize(200, 100);
        local_frame.setVisible(true);

        local_frame.add(new JLabel("Wins: " + wins_m.read()), SwingConstants.CENTER);
        wins_m.reset();
    }

    /**
     * Show new frame with all time highscore
     * @throws IOException exception in case the file is missing or it hasn't been reset
     */
    void show_hscore_action() throws IOException{
        //Create a new frame and display the file data
        JFrame local_frame = new JFrame("Highscores");
        local_frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        local_frame.setSize(200, 100);
        local_frame.setVisible(true);

        local_frame.add(new JLabel(hscores_m.read(), SwingConstants.CENTER));
        hscores_m.reset();
    }

    /**
     * Starts the game with 1 or 2 players
     * Sets questions from round pool (single or multiplayer) and sets the first question panel
     * @param pl number of players in game (1,2)
     */
    void start(int pl) {
        no_of_players = pl;

        //Request single or multiplayer rounds
        Round_Tuple[] rounds_t = (pl == 1)?(Round_Pool.getSinglePlayerRounds(round_count)):(Round_Pool.getMultiPlayerRounds(round_count));
        //Split the tuple array into the logic and gui array
        for (int i = 0; i < round_count; ++i) {
            rounds[i] = rounds_t[i].getRound();
            panels[i] = rounds_t[i].getPanel();
            card.add(panels[i].getPanel(), Integer.toString(i)); //add the gui panel to the card panels
        }

        //Pass through all panels and set the root frame pointer
        for (GUI_Panel panel : panels) panel.setFrame(this);

        //Assign questions to each round, should probably live in the game manager
        //But in the game manager there is no way to know if the player will request single or multiplayer
        //So it needs to be moved here
        for (Round round : rounds) {
            if (pl == 2) {
                //If there are 2 players assign 4 questions (2 duplicates, because multiplayer games should have common questions in each turn)
                //There is no other explanation in the assignment's pdf and not enough time to care about the problems that arise from the common questions
                Question q1 = Round.getNextRandom();
                Question q2 = Round.getNextRandom();
                if (q1 == null || q2 == null) {
                    System.out.println("Not enough questions");
                    return;
                }
                if (round instanceof Quick_Answer_Round) {
                    round.Iquestions[0] = q1;
                    round.Iquestions[1] = q2;
                    round.Iquestions[2] = Round.getNextRandom();
                    round.Iquestions[3] = Round.getNextRandom();
                } else if (round instanceof Thermometer_Round) {
                    round.Iquestions[0] = q1;
                    round.Iquestions[1] = q2;
                    round.Iquestions[2] = Round.getNextRandom();
                    round.Iquestions[3] = Round.getNextRandom();
                    round.Iquestions[4] = Round.getNextRandom();
                    round.Iquestions[5] = Round.getNextRandom();
                    round.Iquestions[6] = Round.getNextRandom();
                    round.Iquestions[7] = Round.getNextRandom();
                } else {
                    round.Iquestions[0] = q1;
                    round.Iquestions[1] = q1;
                    round.Iquestions[2] = q2;
                    round.Iquestions[3] = q2;
                }
            } else {
                round.Iquestions[0] = Round.getNextRandom();
                round.Iquestions[1] = Round.getNextRandom();
            }
            for (Question question : round.Iquestions) {
                if (question == null) {
                    System.out.println("Not enough questions");
                    return;
                }
            }
        }

        //Set first question panel
        panels[0].setQuestion(rounds[0].Iquestions[0]);
        frame.add(card);
        CardLayout cl = (CardLayout) card.getLayout();
        cl.show(card, "0");

        panels[0].getPanel().requestFocus();
        panels[0].reset();//Call reset for the first question in any case, to be safe
    }

    /**
     * provide the players array
     * @param players player objects array
     */
    void setPlayers(Player []players) {
        this.players = players;
    }

    /**
     * calls internally the round logic play function
     * @param choice player's given answer
     */
    void play(int choice) {
        rounds[current_round].play(players, current_player, choice, current_question);
    }

    /**
     * Used when both players play in the current round
     * @param player player that answered
     * @param choice player's given answer
     */
    void play(int player, int choice) {
        rounds[current_round].play(players, player, choice, current_question);

        if (panels[current_round] instanceof Thermometer_Panel) {
            //If the round is (the very problematic) thermometer round, then transfer old thermometer panel counters to the new thermometer panel
            //because every x questions the panels change regardless of the round type
            ((Thermometer_Panel)panels[current_round]).set1(((Thermometer_Round)rounds[current_round]).getC1());
            ((Thermometer_Panel)panels[current_round]).set2(((Thermometer_Round)rounds[current_round]).getC2());

            if (((Thermometer_Round)rounds[current_round]).getC1() == 5 || ((Thermometer_Round)rounds[current_round]).getC2() == 5) {
                forceNext(); //If one player has reached 5, force the next panel
            }
        }
    }

    /**
     * Internally calls the player's setRemainder function
     * @param rem player's remaining time when answering
     */
    void setRemainder(int rem) {
        players[current_player].setRemainder(rem);
    }

    /**
     * Internally calls the player's setBet function
     * @param bet player's chosen bet
     */
    void setBet(int bet) {
        players[current_player].setBet(bet);
    }

    int getNoOfPlayers() { return no_of_players; }

    /**
     * Used by the Thermometer panel, to force feed the next question in the frame when one player has reached 5 correct answers
     */
    void forceNext() {
        current_question = 0;
        current_round++;
        current_player = 0;

        if (end()) return; //If it is time to end the game, return
        CardLayout cl = (CardLayout) card.getLayout();
        cl.show(card, Integer.toString(current_round));

        if (no_of_players == 2) { //if the next panel is too a thermometer or QA panel, signify the concurent playing with current_player = 3
            if (panels[current_round] instanceof Thermometer_Panel || panels[current_round] instanceof Quick_Answer_Panel) {
                current_player = 3;//signify that these panels play concurrently
            } else if (current_player == 3) current_player = 0;//If the last panel was such then reset the current_player to 0
        }

    }

    /**
     * Used to feed the next question or the next round, if the current round has ran out of questions
     */
    void next() {
        if (end()) return;//For some reason I am too dump to understand there need to be 2 IFs before and after the following block
        if (current_question >= rounds[current_round].Iquestions.length - 1) {//If the questions for this round have ran out
            current_question = 0;//Move to the next round
            CardLayout cl = (CardLayout) card.getLayout();
            cl.show(card, Integer.toString(++current_round));
        } else current_question++;
        if (end()) return;

        if (no_of_players == 2) {
            if (current_player >= 1) {
                current_player = 0; //In 2 player mode switch current_player between 0 and 1
            } else current_player++;

            if (panels[current_round] instanceof Thermometer_Panel || panels[current_round] instanceof Quick_Answer_Panel) {
                current_player = 3;//signify that these panels play concurrently
            }
        }
        //In the end do all the stuff for the next question
        panels[current_round].setQuestion(rounds[current_round].Iquestions[current_question]); //Set new question
        panels[current_round].setControls(current_player + 1); //Set new controls
        panels[current_round].setScore1(players[0].getScore()); //Transfer scores
        panels[current_round].setScore2(players[1].getScore());
        panels[current_round].getPanel().requestFocus(); //Request focus (for graphical stuff)
        panels[current_round].reset(); //Call reset in any case to be safe
    }

    /**
     * Method to check if rounds have ran out, and display the appropriate score messages in the end panel
     * @return weather game needs to end
     */
    private boolean end() {
        //Check if rounds have ran out and set appropriate end messages
        if (current_round == rounds.length) {
            score_end_panel.setText("<html>Score 1: " + players[0].getScore());
            if (no_of_players == 2) score_end_panel.setText(score_end_panel.getText() + " Score 2: " + players[1].getScore());

            if (no_of_players == 1 && players[0].getScore() > Integer.parseInt(hscores_m.read())) {
                score_end_panel.setText(score_end_panel.getText() + "<br />Highscore!");
                try {
                    hscores_m.compareAndSwap(players[0].getScore());
                } catch (IOException e) { System.out.println("File error"); }
            }

            if (no_of_players == 2) {//If there are 2 players print who has won
                if (players[0].getScore() == players[1].getScore()) {
                    score_end_panel.setText(score_end_panel.getText() + "<br />Draw!");
                } else {
                    score_end_panel.setText(score_end_panel.getText() + "<br />" + (players[0].getScore()>players[1].getScore()?1:2) + "st player won!");
                    try {
                        wins_m.increaseByOne((players[0].getScore() > players[1].getScore() ? 0 : 1));
                    } catch (IOException e) { System.out.println("File error"); }
                }
            }

            score_end_panel.setText(score_end_panel.getText() + "</html>");

            CardLayout cl = (CardLayout) card.getLayout();
            cl.show(card, "end");
            return true;
        }
        return false;
    }
}
