package Console;

public class Gameflow {
    private static final int NUM_PLAYERS = 2;
    private static final int SIZE = 8;
    private Board board;
    private Player[] players;
    private Logic logic;
    private ConsoleUI display;
    private int validTurns = 0, currentPlayer = 0;

    /**
     * Constructor for Gameflow.
     */
    public Gameflow() {
        ConsoleGameInfo gameInfo = ConsoleGameInfo.getInstance();
        this.board = gameInfo.getBoard();
        this.players = gameInfo.getPlayers();
        this.logic = gameInfo.getLogic();
        this.display = new ConsoleUI();
    }

    /**
     * Runs the games loop.
     */
    public void run() {
        System.out.println("First player is black");
        while (!shouldStop()) {
            playOneTurn();
            this.currentPlayer = (this.currentPlayer + 1) % NUM_PLAYERS;
        }
        //ANNOUNCE WINNER
        System.out.println("No more moves to play");
        this.display.printBoard(this.board);
        int winner = this.logic.getWinner(this.players);
        System.out.println("Scoreboard:");
        System.out.println(this.players[0] + "\t\t\t" + this.players[0].getScore());
        System.out.println(this.players[1] + "\t\t\t" + this.players[1].getScore());
        if (this.players[0].getScore() == this.players[1].getScore())
            System.out.println("It's a tie!");
        else System.out.println("Winner is '" + this.players[winner]
                + "' with score of: " + this.players[winner].getScore());
    }

    /**
     * Plays one move of the game.
     */
    public void playOneTurn() {
        System.out.println("Current board:");
        System.out.println("X: " + this.players[0].getScore() + "\t" + "O" + this.players[1].getScore());
        this.display.printBoard(this.board);
        int temp = this.validTurns;
        this.validTurns += this.players[this.currentPlayer].makeMove(this.board, this.logic);
        if (this.validTurns == temp) {
            this.validTurns = 0;
        }
    }

    /**
     * Checks if the game should end.
     *
     * @return true if board is full or no more moves for a player, false otherwise.
     */
    public boolean shouldStop() {
        return this.board.isFull() || this.validTurns == NUM_PLAYERS;
    }
}