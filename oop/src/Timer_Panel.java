import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Timer_Panel extends GUI_Panel {
    JLabel timer_label;
    Timer  timer;
    int time;

    Timer_Panel() {
        super();

        type.setText("This round is a timer round");

        time = 5000;

        timer_label = new JLabel(Double.toString(time/1000.0));
        timer = new Timer(100, actionEvent -> {
            timer_label.setText(Double.toString((time)/1000.0));
            time -= 100;
            if (time <= 0) {
                timer_label.setText("Time's Up!");
                timer.stop();
            }
        });
        timer.start();

        super.panel.addKeyListener(new KeyListener() {
            @Override
            public void keyTyped(KeyEvent keyEvent) {
                char ans = keyEvent.getKeyChar();
                if (ans != 'a' && ans != 's' && ans != 'd' && ans != 'f') return;

                root_frame.setRemainder(time);
                root_frame.play(translate(ans));
                root_frame.next();
            }

            @Override
            public void keyPressed(KeyEvent keyEvent) { }

            @Override
            public void keyReleased(KeyEvent keyEvent) { }
        });

        super.panel.add(timer_label);
    }

    /**
     * overridden reset method that restarts the countdown
     */
    @Override
    void reset() {
        time = 5000;
        timer.start();
    }
}