package GUI.Listeners;

import GUI.GUICell;
import GUI.GUIGameflow;
import GUI.Utilities.Listener;
import GUI.Utilities.Notifier;

public class CellListener implements Listener {
    private GUIGameflow game;

    /**
     * Constructor for the listener.
     *
     * @param game game to listen to.
     */
    public CellListener(GUIGameflow game) {
        this.game = game;
    }

    @Override
    public void notifyGame(Notifier notifier) {
        GUICell cell = (GUICell) notifier;
        game.makeMove(cell.getCell().getPoint());
    }
}
