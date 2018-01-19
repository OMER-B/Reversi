package Console;

public class Disk {
    private Symbol symbol;

    /**
     * Constructor for the disk by Symbol.
     *
     * @param symbol Symbol for the disk.
     */
    public Disk(Symbol symbol) {
        this.symbol = symbol;
    }

    /**
     * Returns the symbol of the disk.
     *
     * @return Symbol of the disk.
     */
    public Symbol getSymbol() {
        return symbol;
    }

    /**
     * Sets the symbol of the disk.
     *
     * @param symbol Symbol to set for the disk.
     */
    public void setSymbol(Symbol symbol) {
        this.symbol = symbol;
    }
}
