package Console;

public enum Symbol {
    BLACK,
    WHITE,
    EMPTY;

    /**
     * Printable symbols.
     *
     * @return String of the player.
     */
    public String toString() {
        if (this == BLACK) {
            return "X";
        } else if (this == WHITE) {
            return "O";
        } else {
            return " ";
        }
    }
}
