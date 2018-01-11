package GUI;

import Console.Player;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;

public class GUIPlayer {
    private GridPane grid;
    private int height;
    private int width;
    private Player player;
    private Color color;

    public GUIPlayer(GridPane board, int height, int width, Color color) {
        this.grid = board;
        this.height = height;
        this.width = width;
        this.color = color;
    }

    public void draw(int col, int row) {
        Circle circle = new Circle(this.width, this.height, this.height / Reversi.SIZE * 2, this.color);
        this.grid.getChildren().remove(circle);
        this.grid.add(circle, col, row);
    }

    public void makeMove() {
    }

}
