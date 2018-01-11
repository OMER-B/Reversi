package GUI;

import Console.Logic;

public class GUIGameflow {
    private GUIPlayer players[];
    private int currentPlayer;
    private boolean shouldContinue;
    private GUIBoard board;
    private Logic logic;

    public GUIGameflow() {
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        this.board = gameInfo.getBoard();
        this.logic = gameInfo.getLogic();
        this.players = gameInfo.getPlayers();
    }
}
