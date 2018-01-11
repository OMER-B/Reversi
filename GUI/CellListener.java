package GUI;

import Console.Point;

public class CellListener {
    private GUIGameflow game;

    public CellListener(GUIGameflow game) {
        this.game = game;
    }

    public void notifyGame(Point point) {
        game.makeMove(point);
    }
}
