import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class Bet_Panel extends GUI_Panel {
    JPanel card_panel;
    JPanel intro_panel;
    JLabel category_label;
    JButton bet1, bet2, bet3, bet4;

    Bet_Panel() {
        super();

        type.setText("This round is a bet round");
        card_panel = new JPanel();
        card_panel.setLayout(new CardLayout());

        intro_panel = new JPanel();
        category_label = new JLabel();

        intro_panel.setLayout(new FlowLayout());
        intro_panel.add(category_label);

        bet1 = new JButton("250");
        bet1.addActionListener(actionEvent -> setStartFrame(250));
        intro_panel.add(bet1);

        bet2 = new JButton("500");
        bet2.addActionListener(actionEvent -> setStartFrame(500));
        intro_panel.add(bet2);

        bet3 = new JButton("750");
        bet3.addActionListener(actionEvent -> setStartFrame(750));
        intro_panel.add(bet3);

        bet4 = new JButton("1000");
        bet4.addActionListener(actionEvent -> setStartFrame(1000));
        intro_panel.add(bet4);

        card_panel.add(intro_panel, "intro");
        card_panel.add(super.panel, "actual");

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
    @Override
    JPanel getPanel() {
        return card_panel; //Override parent function to return the intro panel instead of the actual
    }

    @Override
    void setQuestion(Question question) {
        super.setQuestion(question);
        category_label.setText("Bet for " + super.category);
    }

    @Override
    void reset() {
        CardLayout cl = (CardLayout) card_panel.getLayout();
        cl.show(card_panel, "intro");
    }

    void setStartFrame(int bet) {
        root_frame.setBet(bet);
        CardLayout cl = (CardLayout) card_panel.getLayout();
        cl.show(card_panel, "actual");
        super.panel.grabFocus();
    }
}
