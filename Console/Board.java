package Console;

public class Board {
    private Cell[][] cells;
    private Counter counter;
    private Player players[];
    private int size;

    /**
     * Constructor for the board. Calls the initialize() method.
     *
     * @param size    size of the board.
     * @param players array of two players.
     */
    public Board(int size, Player players[]) {
        this.counter = new Counter(4);
        this.size = size;
        this.players = players;
        this.initalize();
    }

    /**
     * Initializes the board with the players in the middle.
     */
    public void initalize() {
        this.cells = new Cell[this.size][this.size];
        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                this.cells[i][j] = new Cell(i, j);
                this.cells[i][j].setX(i);
                this.cells[i][j].setY(j);
            }
        }
        this.cells[(this.size / 2) - 1][(this.size / 2) - 1].fill(players[0]);
        this.cells[(this.size / 2)][(this.size / 2)].fill(players[0]);
        this.cells[(this.size / 2) - 1][(this.size / 2)].fill(players[1]);
        this.cells[(this.size / 2)][(this.size / 2) - 1].fill(players[1]);
    }

    /**
     * Returns the cell at position (i,j) of the board.
     *
     * @param i vertical position of the requested cell.
     * @param j horizonal position of the requested cell.
     * @return cell at position (i,j).
     */
    public Cell getCell(int i, int j) {
        return this.cells[i][j];
    }

    /**
     * Returns the player at position (i,j) of the board.
     *
     * @param i vertical position of the requested cell.
     * @param j horizonal position of the requested cell.
     * @return player at cell (i,j).
     */
    public Player getPlayer(int i, int j) {
        return this.cells[i][j].getPlayer();
    }

    /**
     * Returns the player at the given point.
     *
     * @param point requested point location for the player
     * @return player at the location of the point.
     */
    public Player getPlayer(Point point) {
        return this.cells[point.getX()][point.getY()].getPlayer();
    }

    /**
     * Returns if the input x, y coordinates are in the board's boundaries.
     *
     * @param x coordinate to check
     * @param y coordinate to check
     * @return true if (x,y) is a valid coordinate, false otherwise.
     */
    public boolean inBoundaries(int x, int y) {
        return (x >= 0 && y >= 0 && x < this.size && y < this.size);
    }

    /**
     * Returns if the input point is in the board's boundaries.
     *
     * @param point point to check
     * @return true if the point is in valid range, false otherwise.
     */
    public boolean inBoundaries(Point point) {
        return (point.getX() >= 0 && point.getY() >= 0 && point.getX() < this.size && point.getY() < this.size);

    }

    /**
     * Returns the size of the board.
     *
     * @return an integer size of the board.
     */
    public int getSize() {
        return this.size;
    }

    /**
     * Fills cell with a player.
     *
     * @param point  point which cell's to fill
     * @param player player to fill with
     */
    public void fillCell(Point point, Player player) {
        if (cells[point.getX()][point.getY()].isEmpty()) {
            this.counter.increaseCounter();
        }
        this.cells[point.getX()][point.getY()].fill(player);
    }

    /**
     * Checks if the board is full or not.
     *
     * @return true if the board is full, false otherwise.
     */
    public boolean isFull() {
        return this.counter.getValue() == (this.size * this.size);
    }
}