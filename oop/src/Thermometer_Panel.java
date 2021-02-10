import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

/**
 * @author Ioannis Manthopoulos
 */
public class Thermometer_Panel extends GUI_Panel {
    JLabel p1;
    JLabel p2;
    int c1;
    int c2;

    Thermometer_Panel() {
        super();

        type.setText("This round is a thermometer round");
        c1 = 0;//Counters used only in thermometer game
        c2 = 0;

        p1 = new JLabel(Integer.toString(c1));
        p2 = new JLabel(Integer.toString(c2));
        super.panel.add(p1);
        super.panel.add(p2);

        super.panel.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent keyEvent) {
            }

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
    void set1(int c) { p1.setText(Integer.toString(c)); }
    void set2(int c) { p2.setText(Integer.toString(c)); }
}
