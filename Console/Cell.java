package Console;

public class Cell {
    private Point point;
    private Player player;

    /**
     * Constructor for a cell by x, y coordinates.
     *
     * @param x coordinate for the cell.
     * @param y coordinate for the cell.
     */
    public Cell(int x, int y) {
        this.point = new Point(x, y);
    }

    /**
     * Returns the occupying player's symbol.
     *
     * @return occupying player's symbol.
     */
    public Symbol getSymbol() {
        return this.player == null ? Symbol.EMPTY : this.player.getSymbol();
    }

    public Point getPoint() {
        return this.point;
    }

    /**
     * Returns the x coordinate of the cell.
     *
     * @return x coordinate of the cell.
     */
    public int getX() {
        return this.point.getX();
    }

    /**
     * Sets the x coordinate of the cell to given x.
     *
     * @param x new coordinate of the cell.
     */
    public void setX(int x) {
        this.point.setX(x);
    }

    /**
     * Returns the y coordinate of the cell.
     *
     * @return y coordinate of the cell.
     */
    public int getY() {
        return this.point.getY();
    }

    /**
     * Sets the y coordinate of the cell to given y.
     *
     * @param y new coordinate of the cell.
     */
    public void setY(int y) {
        this.point.setY(y);
    }

    /**
     * Returns the occupying player of the cell.
     *
     * @return occupying player of the cell.
     */
    public Player getPlayer() {
        return this.player;
    }

    /**
     * Checks if the cell is empty.
     *
     * @return true if cell is empty, false otherwise.
     */
    public boolean isEmpty() {
        return this.player == null;
    }

    /**
     * Fills the cell with a player.
     *
     * @param player player to fill the cell with.
     */
    public void fill(Player player) {
        this.player = player;
    }
}