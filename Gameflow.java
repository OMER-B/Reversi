public class Gameflow {
    private Board board;
    private Player[] players;
    private Logic logic;
    private int numOfPlayers = 2, validTurns = 0, currentPlayer = 0;
    private Display display;


    public Gameflow() {
        this.display = new Display();
        this.logic = new regLogic();
        this.players = new Player[2];
        this.players[0] = new Player('X');
        this.players[1] = new Player('O');
        this.board = new Board(4, 4, this.players);
    }

    public void run() {
        System.out.println("First player is black");
        while (!shouldStop()) {
            playOneTurn();
        }
        //ANNOUNCE WINNER
        Player winner = this.logic.getWinner(this.players);
        System.out.println("Winner is" + winner);
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
            this.currentPlayer = (this.currentPlayer + 1) % this.numOfPlayers;
        }
        System.out.println("No more moves to play");
        this.display.printBoard(this.board);

    }

    public boolean shouldStop() {
        return this.board.isFull();
    }
}
