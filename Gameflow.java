public class Gameflow {
    private Board board;
    private Player[] players;
    private Logic logic;
    private Display display;
    private int validTurns = 0, currentPlayer = 0;
    private static final int NUM_PLAYERS = 2;
    private static final int SIZE = 8;

    public Gameflow() {
        this.display = new Display();
        this.logic = new regLogic();
        this.players = new Player[2];
        this.players[0] = new Player('X');
        this.players[1] = new Player('O');
        this.board = new Board(SIZE, this.players);
    }

    public void run() {
        System.out.println("First player is black");
        while (!shouldStop()) {
            playOneTurn();
        }
        //ANNOUNCE WINNER
        Player winner = this.logic.getWinner(this.players);
        System.out.println("Scoreboard:");
        System.out.println(this.players[0] + "\t\t\t" + this.players[0].getScore());
        System.out.println(this.players[1] + "\t\t\t" + this.players[1].getScore());
        if (this.players[0].getScore() == this.players[1].getScore()) System.out.println("It's a tie!");
        else System.out.println("Winner is '" + winner + "' with score of: " + winner.getScore());
    }

    public void playOneTurn() {
        while (!shouldStop()) {
            System.out.println("Current board:");
            this.display.printBoard(this.board);
            int temp = this.validTurns;
            this.validTurns += this.players[this.currentPlayer].makeMove(this.board, this.logic);
            if (this.validTurns == temp) {
                this.validTurns = 0;
            }
            this.currentPlayer = (this.currentPlayer + 1) % NUM_PLAYERS;
        }
        System.out.println("No more moves to play");
        this.display.printBoard(this.board);

    }

    public boolean shouldStop() {
        return this.board.isFull() || this.validTurns == NUM_PLAYERS;
    }
}