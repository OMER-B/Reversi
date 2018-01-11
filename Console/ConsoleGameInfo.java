package Console;

import static Console.Symbol.BLACK;
import static Console.Symbol.WHITE;

public class ConsoleGameInfo {

    private static ConsoleGameInfo ourInstance = new ConsoleGameInfo();

    public static ConsoleGameInfo getInstance() {
        return ourInstance;
    }

    private Player[] players;
    private Board board;
    private Logic logic;

    public ConsoleGameInfo() {
        this.logic = new regLogic();
        this.players = new Player[2];
        this.players[0] = new Player(new Disk(BLACK));
        this.players[1] = new Player(new Disk(WHITE));
        this.board = new Board(GUI.Reversi.SIZE, players);
        }


    public Player[] getPlayers() {
        return players;
    }

    public void setPlayers(Player[] players) {
        this.players = players;
    }

    public Board getBoard() {
        return board;
    }

    public void setBoard(Board board) {
        this.board = board;
    }

    public Logic getLogic() {
        return logic;
    }

    public void setLogic(Logic logic) {
        this.logic = logic;
    }
}
