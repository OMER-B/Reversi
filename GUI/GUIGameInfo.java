package GUI;

import Console.Logic;
import Console.Player;
import Console.Symbol;
import Console.regLogic;
import GUI.Controllers.GUIBoard;
import GUI.Listeners.CellListener;

public class GUIGameInfo {
    private static GUIGameInfo ourInstance = new GUIGameInfo();
    private Player[] players;
    private GUIBoard board;
    private Logic logic;
    private GUIGameflow game;
    private CellListener listener;
    private GUIPlayer[] guiPlayers;

    /**
     * Constructor for the GameInfo.
     */
    private GUIGameInfo() {
        this.board = new GUIBoard();
        this.logic = new regLogic();
        this.players = new Player[2];
        this.players[0] = new Player(Symbol.BLACK);
        this.players[1] = new Player(Symbol.WHITE);
        this.guiPlayers = new GUIPlayer[2];
        this.guiPlayers[0] = new GUIPlayer(this.players[0]);
        this.guiPlayers[1] = new GUIPlayer(this.players[1]);

    }

    /**
     * @return instance of the info. It's a singleton.
     */
    public static GUIGameInfo getInstance() {
        return ourInstance;
    }

    /**
     * Returns the current game.
     *
     * @return return the game.
     */
    public GUIGameflow getGame() {
        return game;
    }

    /**
     * Returns the gui players of the game.
     *
     * @return Array of GUIPlayers.
     */
    public GUIPlayer[] getGUIPlayers() {
        return this.guiPlayers;
    }

    public void setGame() {
        this.game = new GUIGameflow();
        this.listener = new CellListener(game);
    }

    /**
     * Returns the game's listener.
     *
     * @return listener of the game.
     */
    public CellListener getListener() {
        return listener;
    }

    /**
     * Returns the players of the game.
     *
     * @return Array of Players.
     */
    public Player[] getPlayers() {
        return this.players;
    }

    /**
     * Returns the GUIBoard of the game.
     *
     * @return GUIBoard of the game.
     */
    public GUIBoard getBoard() {
        return board;
    }

    /**
     * Sets the GUIBoard of the game.
     *
     * @param board GUIBoard to set.
     */
    public void setBoard(GUIBoard board) {
        this.board = board;
    }

    /**
     * Returns the Logic of the game.
     *
     * @return Logic to return.
     */
    public Logic getLogic() {
        return logic;
    }

}
