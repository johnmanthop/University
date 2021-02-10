import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

/**
 * Graphical Interface class representing the JPanel for the quick answer type of round
 * @author Ioannis Manthopoulos
 */
public class Quick_Answer_Panel extends GUI_Panel {

    Quick_Answer_Panel() {
        super();

        type.setText("This round is a quick answer round");

        super.panel.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent keyEvent) {  }

            @Override
            public void keyPressed(KeyEvent keyEvent) {
                char ans = keyEvent.getKeyChar();
                if ((ans != 'a' && ans != 's' && ans != 'd' && ans != 'f') &&
                        ((ans != 'u' && ans != 'i' && ans != 'o' && ans != 'p'))) return;

                root_frame.play((ans=='a'||ans=='s'||ans=='d'||ans=='f')?0:1, translate(ans));

                root_frame.next();
            }

            @Override
            public void keyReleased(KeyEvent keyEvent) { }
        });
    }
}
