package GUI;

import Console.Cell;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Rectangle;

import static Console.Symbol.BLACK;
import static Console.Symbol.WHITE;

public class GUICell extends Rectangle {
    private Cell cell;
    private GUIBoard board;

    public GUICell(double width, double height, Paint fill, Cell cell) {
        super(width, height, fill);
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        this.board = gameInfo.getBoard();
        this.cell = cell;
        this.setFill(Color.DARKGREEN);
    }

    public void draw() {
        this.setStroke(Color.BLACK);
        if (this.cell.getSymbol() == BLACK) {
            this.setFill(Color.BLACK);
        } else if (this.cell.getSymbol() == WHITE) {
            this.setFill(Color.WHITE);
        }
        this.board.getChildren().remove(this);
        this.board.add(this, this.cell.getX(), this.cell.getY());

    }

    //handle click - notify game
}
