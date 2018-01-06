import java.util.Scanner;
import java.util.Vector;

public class Player {
    private char symbol;
    private Counter score;

    public Player(char symbol) {
        this.symbol = symbol;
        this.score = new Counter(2);
    }

    public char getSymbol() {
        return symbol;
    }

    public int getScore() {
        return this.score.getValue();
    }

    public void setScore(int score) {
        this.score.setValue(score);
    }

    public void increaseScore() {
        this.score.increaseCounter();
    }

    public void decreaseScore() {
        this.score.decreaseCounter();
    }

    public int compare(Player player) {
        return Integer.compare(this.score.getValue(), player.getScore());
    }

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

    public String toString() {
        return Character.toString(this.symbol);
    }
}