import javax.swing.*;

/**
 * author: Ioannis Manthopoulos
 */
public abstract class GUI_Panel {
    protected JPanel panel;
    protected String category;
    protected GUI_Frame root_frame;
    protected JLabel type;

    int pl1_points;
    int pl2_points;

    JLabel pl1_points_l;
    JLabel pl2_points_l;
    JLabel question_label;
    JLabel controls_label;
    JLabel image_label;

    JLabel answers_field;
    ImageIcon image;

    /**
     * Initialize panel elements
     */
    GUI_Panel() {
        type           = new JLabel("", SwingConstants.CENTER);
        panel          = new JPanel();
        question_label = new JLabel("", SwingConstants.CENTER);
        answers_field  = new JLabel("", SwingConstants.CENTER);
        controls_label = new JLabel("", SwingConstants.CENTER);
        image_label    = new JLabel("", SwingConstants.CENTER);
        image = null;

        pl1_points = 0;
        pl2_points = 0;
        pl1_points_l = new JLabel("Player 1 score 0");
        pl2_points_l = new JLabel("Player 2 score 0");

        if (this instanceof Thermometer_Panel || this instanceof Quick_Answer_Panel) {
            controls_label.setText("Both players play");
        } else {
            controls_label.setText("Player 1 turn");
        }

        panel.setFocusable(true);
        panel.setLayout(new BoxLayout(panel, BoxLayout.PAGE_AXIS));
        panel.add(question_label);
        panel.add(image_label);
        panel.add(answers_field);
        panel.add(controls_label);
        panel.add(type);
    }

    int translate(char k) {
        if (k == 'a' || k == 'u') return 1;
        if (k == 's' || k == 'i') return 2;
        if (k == 'd' || k == 'o') return 3;
        if (k == 'f' || k == 'p') return 4;
        return -1;
    }

    /**
     * Sets the controls label, meaning whether the current player is 1, 2 or both play at the same time
     * @param p the current player's turn, can be 1, 2 or 4(= both players play)
     */
    void setControls(int p) {
        String to_set;
        if (p == 4) {
            to_set = "Both players play";
        } else {
            to_set = "Player " + p + " turn";
        }
        controls_label.setText(to_set);
    }

    /**
     * Sets the question info to be displayed
     * @param question the question to be displayed
     */
    void setQuestion(Question question) {
        question_label.setText("<html><center>" + question.getQuestion() + "</center></html>");
        if (question.getSpecial() != null) { //If the question has an image associated
            setImage(question.getSpecial()); //Set that image in the panel
        } else {
            removeImage(); //else remove any image that may be left from before
        }
        category = question.getCategory();
        StringBuilder total_text = new StringBuilder();
        total_text.append("<html><center><br /><br />");
        int i = 0;
        for (String answer : question.getAnswers()) total_text.append(++i).append('-').append(answer).append("<br />");
        total_text.append("<br /><br /></center></html>");

        answers_field.setText(total_text.toString());
    }

    /**
     * Sets an image in case the question is an image question
     * @param image_path the file path to the image
     */
    void setImage(String image_path) {
        image = new ImageIcon(image_path);
        image_label.setIcon(image);
        root_frame.frame.setSize(550, 450);
    }

    /**
     * Removes previous image in case the current question is not an image question
     */
    void removeImage() {
        image_label.setIcon(null);
        root_frame.frame.setSize(550, 300);
    }

    /**
     * Sets the player 1 score
     * @param sc player 1 score
     */
    void setScore1(int sc) {
        pl1_points = sc;
        pl1_points_l.setText("Player 1 score " + sc);
    }

    /**
     * Sets the player 2 score (only in multiplayer mode)
     * @param sc player 2 score
     */
    void setScore2(int sc) {
        pl2_points = sc;
        if (pl2_points_l != null) pl2_points_l.setText("Player 2 score " + sc);
    }

    /**
     * Returns the configured jpanel to the gui frame
     * @return the jpanel of the round
     */
    JPanel getPanel() {
        return panel;
    }

    /**
     * Sets root frame for the panel
     * @param fr root frame
     */
    void setFrame(GUI_Frame fr) {
        root_frame = fr;
        panel.add(pl1_points_l);
        if (root_frame.getNoOfPlayers() == 2) panel.add(pl2_points_l);
    }

    /**
     * reset method, to be overridden by any round that needs some kind of reset
     */
    void reset() {}
}
