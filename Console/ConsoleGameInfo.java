package Console;

import GUI.Utilities.SettingsInfo;

import static Console.Symbol.BLACK;
import static Console.Symbol.WHITE;

public class ConsoleGameInfo {

    private static ConsoleGameInfo ourInstance = new ConsoleGameInfo();
    private Player[] players;
    private Board board;
    private Logic logic;

    /**
     * Constructor for the Console Game Info
     */
    public ConsoleGameInfo() {
        this.logic = new regLogic();
        this.players = new Player[2];
        this.players[0] = new Player(new Disk(BLACK));
        this.players[1] = new Player(new Disk(WHITE));
        this.board = new Board(SettingsInfo.getInstance().getSize(), players);
    }

    /**
     * @return ConsoleGameInfo the instance of the CGI. It's a singleton.
     */
    public static ConsoleGameInfo getInstance() {
        return ourInstance;
    }

    /**
     * Returns the players of the game.
     *
     * @return Players[] the players of the game.
     */
    public Player[] getPlayers() {
        return players;
    }

    /**
     * Returns the board of the game.
     *
     * @return Board board of the game.
     */
    public Board getBoard() {
        return board;
    }

    /**
     * Sets the board of the game.
     *
     * @param board board to set.
     */
    public void setBoard(Board board) {
        this.board = board;
    }

    /**
     * Returns the logic of the game.
     *
     * @return Logic the logic of the game
     */
    public Logic getLogic() {
        return logic;
    }
}
