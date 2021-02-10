/**
 * Tuple class representing a tuple of a round logic and round gui classes
 * @author Ioannis Manthopoulos
 */
public class Round_Tuple {
    Round round;
    GUI_Panel panel;

    Round_Tuple(Round r, GUI_Panel p) {
        round = r;
        panel = p;
    }

    Round getRound() { return round; }
    GUI_Panel getPanel() { return panel; }
}
