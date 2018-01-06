public class Board {
    private Cell[][] cells;
    private Counter counter;
    private Player players[];
    private int size;

    public Board(int size, Player players[]) {
        this.counter = new Counter(4);
        this.size = size;
        this.cells = new Cell[this.size][this.size];
        this.players = players;
        this.initalize();
    }

    public void initalize() {
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

    public Cell getCell(int i, int j) {
        return this.cells[i][j];
    }

    public Player getPlayer(int i, int j) {
        return this.cells[i][j].getPlayer();
    }

    public Player getPlayer(Point point) {
        return this.cells[point.getX()][point.getY()].getPlayer();
    }

    public boolean inBoundaries(int x, int y) {
        return (x >= 0 && y >= 0 && x < this.size && y < this.size);
    }

    public boolean inBoundaries(Point point) {
        return (point.getX() >= 0 && point.getY() >= 0 && point.getX() < this.size && point.getY() < this.size);

    }

    public int getSize() {
        return this.size;
    }

    public void fillCell(Point point, Player player) {
        if (cells[point.getX()][point.getY()].isEmpty()) {
            this.counter.increaseCounter();
        }
        this.cells[point.getX()][point.getY()].fill(player);
    }

    public boolean isFull() {
        return this.counter.getValue() == (this.size * this.size);
    }
}