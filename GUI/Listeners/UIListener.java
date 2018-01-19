package GUI.Listeners;

import GUI.GUIPlayer;
import GUI.Utilities.Listener;
import GUI.Utilities.Notifier;
import javafx.scene.control.Label;

public class UIListener implements Listener {

    private Label label;

    /**
     * Constructor for the listener.
     *
     * @param label label to listen to.
     */
    public UIListener(Label label) {
        this.label = label;
    }

    @Override
    public void notifyGame(Notifier notifier) {
        GUIPlayer player = (GUIPlayer) notifier;
        label.setTextFill(player.getColor());
        label.setText("Current Player");
    }
}
