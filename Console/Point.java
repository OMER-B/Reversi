package Console;

public class Point {
    private int x;
    private int y;

    /**
     * Constructor for point by coordinates.
     *
     * @param x coordinate for point.
     * @param y coordinate for point.
     */
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Sets x coordinate of the point.
     *
     * @return x coordinate of the point.
     */
    public int getX() {
        return this.x;
    }

    /**
     * Sets y coordinate of the point.
     *
     * @param x y coordinate of the point.
     */
    public void setX(int x) {
        this.x = x;
    }

    /**
     * Returns y coordinate of the point.
     *
     * @return y coordinate of the point.
     */
    public int getY() {
        return this.y;
    }

    /**
     * Returns x coordinate of the point.
     *
     * @return x coordinate of the point.
     */
    public void setY(int y) {
        this.y = y;
    }

    /**
     * Makes the string printable.
     *
     * @return String the printable string.
     */
    public String toString() {
        return "(" + this.x + ", " + this.y + ")";
    }
}