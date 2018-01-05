public class Board {
    private Cell[][] cells;
    private int counter;
    private Player players[];
    private int width;
    private int height;

    public Board(int width, int height, Player players[]) {
        this.width = width;
        this.height = height;
        this.cells = new Cell[this.width][this.height];
        this.players = players;
        this.initalize();
    }

    public void initalize() {
        for (int i = 0; i < this.width; i++) {
            for (int j = 0; j < this.height; j++) {
                this.cells[i][j] = new Cell(i, j);
                this.cells[i][j].setX(i);
                this.cells[i][j].setY(j);
            }
        }
        this.cells[(this.width / 2) - 1][(this.height / 2) - 1].fill(players[0]);
        this.cells[(this.width / 2)][(this.height / 2)].fill(players[0]);
        this.cells[(this.width / 2) - 1][(this.height / 2)].fill(players[1]);
        this.cells[(this.width / 2)][(this.height / 2) - 1].fill(players[1]);
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
        return (x >= 0 && y >= 0 && x < this.width && y < this.height);
    }

    public boolean inBoundaries(Point point) {
        return (point.getX() >= 0 && point.getY() >= 0 && point.getX() < this.width && point.getY() < this.height);

    }

    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }

    public void fillCell(Point point, Player player) {
        if (cells[point.getX()][point.getY()].isEmpty()) {
            counter++;
        }
        this.cells[point.getX()][point.getY()].fill(player);
    }

    public boolean isFull() {
        return false;
    }
}
