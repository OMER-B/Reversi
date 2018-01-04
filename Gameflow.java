public class Gameflow {
    private Board board;
    private Player[] players;
    private Logic logic;

    public Game() {
        this.players[0] = new Player('X');
        this.players[1] = new Player('O');
        this.board = new Board(8, 8, players);
    }

    public void run() {
        while (shouldStop()) {
            playOneTurn();
        }
        //ANNOUNCE WINNER
    }

    public void playOneTurn() {

    }

    public boolean shouldStop() {
        return this.board.isFull();
    }
}
