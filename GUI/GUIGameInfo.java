package GUI;

import Console.Logic;
import Console.regLogic;
import javafx.scene.paint.Color;

public class GUIGameInfo {
    private static GUIGameInfo ourInstance = new GUIGameInfo();

    public static GUIGameInfo getInstance() {
        return ourInstance;
    }

    private GUIPlayer[] players;
    private GUIBoard board;
    private Logic logic;

    private GUIGameInfo() {
        this.board = new GUIBoard();

        int height = (int) this.board.getPrefWidth();
        int width = (int) this.board.getPrefWidth();
        Color color1 = Color.BLACK;
        Color color2 = Color.WHITE;
        this.logic = new regLogic();
        this.players = new GUIPlayer[2];
        this.players[0] = new GUIPlayer(this.board, height, width, color1);
        this.players[1] = new GUIPlayer(this.board, height, width, color2);

        this.board.addPlayers(this.players);
    }

    public GUIPlayer[] getPlayers() {
        return this.players;
    }

    public void setPlayers(GUIPlayer[] players) {
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
