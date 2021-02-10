import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Correct_Answer_Panel extends GUI_Panel {
    Correct_Answer_Panel() {
        super();

        type.setText("This round is a correct answer round");
        super.panel.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent keyEvent) {
                char ans = keyEvent.getKeyChar();
                if (ans != 'a' && ans != 's' && ans != 'd' && ans != 'f') return;

                root_frame.play(translate(ans));
                root_frame.next();
            }

            @Override
            public void keyPressed(KeyEvent keyEvent) { }

            @Override
            public void keyReleased(KeyEvent keyEvent) { }
        });
    }
}
