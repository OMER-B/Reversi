package Console;

public class ConsoleUI {
    /**
     * Prints the board to the console.
     *
     * @param board board to print.
     */
    public void printBoard(Board board) {
        int boardSize = board.getSize();
        System.out.print("+");
        for (int j = 0; j <= boardSize; j++) {
            System.out.print("---+");
        }
        System.out.println();
        System.out.print("|   | ");
        for (int i = 0; i < boardSize; i++) {
            System.out.print(i + " | ");
        }
        System.out.println();
        System.out.print("+");
        for (int j = 0; j <= boardSize; j++) {
            System.out.print("---+");
        }
        System.out.println();
        for (int i = 0; i < boardSize; i++) {
            System.out.print("| " + i + " | ");
            for (int j = 0; j < boardSize; j++) {
                System.out.print(board.getCell(j, i).getSymbol() + " | ");
            }
            System.out.println();
            System.out.print("+");

            for (int k = 0; k <= boardSize; k++) {
                System.out.print("---+");
            }
            System.out.println();
        }
    }
}