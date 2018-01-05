public class Cell {
    private Point point;
    private Player player;

    public Cell(int x, int y) {
        this.point = new Point(x, y);
    }

    public Cell(Point point) {

        this.point = point;
    }

    public char getSymbol() {
        if (this.player == null) {
            return ' ';
        }
        return this.player.getSymbol();
    }

    public int getX() {
        return this.point.getX();
    }

    public void setX(int x) {
        this.point.setX(x);
    }

    public int getY() {
        return this.point.getY();
    }

    public void setY(int y) {
        this.point.setY(y);
    }

    public Player getPlayer() {
        return this.player;
    }

    public boolean isEmpty() {
        return this.player == null;
    }

    public void fill(Player player) {
        this.player = player;
    }
}
