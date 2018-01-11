package Console;

public enum Symbol {
    BLACK,
    WHITE,
    EMPTY;

    public static String toString(Symbol symbol) {
        if (symbol == BLACK) {
            return "X";
        } else if (symbol == WHITE) {
            return "O";
        } else {
            return " ";
        }
    }
}
