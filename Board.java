public class Board {
    Cell[][] cells;
    int counter;
    Player players[];
    private int width;
    private int height;

    public Board(int width, int height, Player players[]) {
        this.width = width;
        this.height = height;
        this.players = players;
        this.initalize();
    }

    public void initalize() {
        for (int i = 0; i < this.width; i++) {
            for (int j = 0; j < this.height; j++) {
                cells[i][j].setX(i);
                cells[i][j].setY(j);
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

    public boolean inBoundaries(int x, int y) {
        return (x >= 0 && y >= 0 && x < this.width && y < this.height);
    }

    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }

    public boolean isFull() {

    }
}
