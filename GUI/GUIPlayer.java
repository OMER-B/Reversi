package GUI;

import Console.Board;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class GUIPlayer {
    private GridPane grid;
    private int height;
    private int width;
    private ImageView iv;
    private int symbol;
    private Board board;
    private Color[] color = {new Color(1, 1, 1, 1),
            new Color(0, 0, 0, 1)};

    public GUIPlayer(GridPane grid, int symbol, Board board, int height, int width) {
        this.grid = grid;
        this.symbol = symbol;
        this.board = board;
        this.height = height;
        this.width = width;
    }

    public void draw(int col, int row) {
        Circle circle = new Circle(this.width, this.height, this.height / Reversi.SIZE * 2, color[1 - symbol]);
        grid.add(circle, col, row);
        grid.getChildren().remove(circle);
        grid.add(circle, col, row);
    }

    public void makeMove() {
    }

}
