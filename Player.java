import java.util.Scanner;
import java.util.Vector;

public class Player {
    private char symbol;
    private Score score;

    public Player(char symbol) {
        this.symbol = symbol;
        this.score = new Score();
    }

    public char getSymbol() {
        return symbol;
    }

    public int getScore() {
        return this.score.getScore();
    }

    public void setScore(int score) {
        this.score.setScore(score);
    }

    public void increaseScore() {
        this.score.increaseScore();
    }

    public void decreaseScore() {
        this.score.decreaseScore();
    }

    public int compare(Player player) {
        return Integer.compare(this.score.getScore(), player.getScore());
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
            Scanner numberScanner = new Scanner(System.in);
            moveX = numberScanner.nextInt();
            moveY = numberScanner.nextInt();


            if (board.inBoundaries(moveX, moveY) && logic.isOptionInList(new Point(moveX, moveY), possibleMoves)) {
                break;
            }
            System.out.println("Invalid input. Try again.");
        }
        Point newCell = new Point(moveX, moveY);
        logic.putNewCell(board, this, newCell);
        return 0;
    }
}
