package Console;

import java.util.Scanner;
import java.util.Vector;

public class Player {
    private Disk symbol;

    private Counter score;

    /**
     * Constructor for player.
     *
     * @param symbol symbol for the player.
     */
    public Player(Symbol symbol) {
        this.symbol = new Disk(symbol);
        this.score = new Counter(2);
    }

    /**
     * @param symbol Constructor by given Disk.
     */
    public Player(Disk symbol) {
        this.symbol = symbol;
        this.score = new Counter(2);
    }

    /**
     * Returns the player's symbol.
     *
     * @return symbol of the player.
     */
    public Symbol getSymbol() {
        return this.symbol.getSymbol();
    }

    /**
     * @return Returns disk of the player.
     */
    public Disk getDisk() {
        return this.symbol;
    }

    /**
     * Returns the score of the player.
     *
     * @return score of the player.
     */
    public int getScore() {
        return this.score.getValue();
    }

    /**
     * Sets the score of the player.
     *
     * @param score new Score to set.
     */
    public void setScore(int score) {
        this.score.setValue(score);
    }

    /**
     * Increases the score of the player.
     */
    public void increaseScore() {
        this.score.increaseCounter();
    }

    /**
     * Decreases the score of the playre.
     */
    public void decreaseScore() {
        this.score.decreaseCounter();
    }

    /**
     * Makes a move to the player.
     *
     * @param board board to make the move on.
     * @param logic logic to use for the move.
     * @return 0 if move is successful, 1 if no moves available and 2 if game ends.
     */
    public int makeMove(Board board, Logic logic) {
        System.out.println(this.getSymbol() + ", it's your turn.");
        Vector<Point> possibleMoves = new Vector<>();
        possibleMoves = logic.getOptionalMoves(board, this);
        if (possibleMoves.isEmpty()) {
            System.out.println("You don't have any moves. Trying next player.");
            return 1;
        }
        System.out.print("Possible moves: ");
        for (Point moves : possibleMoves) {
            System.out.print(moves);
        }
        System.out.println();
        int moveX = -1, moveY = -1;
        System.out.println("Enter your move 'row col': ");
        while (true) {
            try {
                Scanner numberScanner = new Scanner(System.in);
                moveX = numberScanner.nextInt();
                moveY = numberScanner.nextInt();

            } catch (Exception e) {
                System.out.println("Game has ended by request from '" + this + "'.");
                return 2;
            }
            if (board.inBoundaries(moveX, moveY) && logic.isOptionInList(new Point(moveX, moveY), possibleMoves)) {
                break;
            }
            System.out.println("Input not in list of moves. Try again.");
        }
        Point newCell = new Point(moveX, moveY);
        logic.putNewCell(board, this, newCell);
        return 0;
    }

    /**
     * Printable symbol of the player.
     *
     * @return Symbol of the player
     */
    public String toString() {
        return this.symbol.getSymbol().toString();
    }
}