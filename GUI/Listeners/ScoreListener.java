package GUI.Listeners;

import GUI.GUIPlayer;
import GUI.Utilities.Listener;
import GUI.Utilities.Notifier;
import javafx.scene.control.Label;

public class ScoreListener implements Listener {
    private Label label;

    /**
     * Constructor for the listener.
     *
     * @param label label to listen to.
     */
    public ScoreListener(Label label) {
        this.label = label;
    }

    @Override
    public void notifyGame(Notifier notifier) {
        GUIPlayer player = (GUIPlayer) notifier;
        this.label.setTextFill(player.getColor());
        this.label.setText("Score: " + player.getPlayer().getScore());
    }
}
