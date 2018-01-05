public class Display {
    void printBoard(Board board) {
        int x = board.getWidth();
        int y = board.getHeight();
        System.out.print("+");
        for (int j = 0; j <= y; j++) {
            System.out.print("---+");
        }
        System.out.println();
        System.out.print("|   | ");
        for (int i = 0; i < x; i++) {
            System.out.print(i + " | ");
        }
        System.out.println();
        System.out.print("+");
        for (int j = 0; j <= y; j++) {
            System.out.print("---+");
        }
        System.out.println();
        for (int i = 0; i < y; i++) {
            System.out.print("| " + i + " | ");
            for (int j = 0; j < x; j++) {
                System.out.print(board.getCell(i, j).getSymbol() + " | ");
            }
            System.out.println();
            System.out.print("+");

            for (int k = 0; k <= y; k++) {
                System.out.print("---+");
            }
            System.out.println();
        }
    }
}
