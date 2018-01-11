package GUI;

import Console.Logic;
import Console.Player;
import Console.Symbol;
import Console.regLogic;
import javafx.scene.paint.Color;

public class GUIGameInfo {
    private static GUIGameInfo ourInstance = new GUIGameInfo();

    public static GUIGameInfo getInstance() {
        return ourInstance;
    }

    private Player[] players;
    private GUIBoard board;
    private Logic logic;
    private GUIGameflow game;
    private CellListener listener;

    private GUIGameInfo() {
        this.board = new GUIBoard();
        this.logic = new regLogic();
        this.players = new Player[2];
        this.players[0] = new Player(Symbol.BLACK);
        this.players[1] = new Player(Symbol.WHITE);
        this.game = new GUIGameflow();
        this.listener = new CellListener(game);
    }

    public GUIGameflow getGame() {
        return game;
    }

    public void setGame(GUIGameflow game) {
        this.game = game;
    }

    public CellListener getListener() {
        return listener;
    }

    public void setListener(CellListener listener) {
        this.listener = listener;
    }

    public Player[] getPlayers() {
        return this.players;
    }

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public GUIBoard getBoard() {
        return board;
    }

    public void setBoard(GUIBoard board) {
        this.board = board;
    }

    public Logic getLogic() {
        return logic;
    }

    public void setLogic(Logic logic) {
        this.logic = logic;
    }
}
