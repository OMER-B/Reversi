package GUI;

import Console.Board;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class GUIBoard extends GridPane {

    private Board board;

    public GUIBoard(Board board) {
        this.board = board;
    }

    public void draw() {


        this.getChildren().clear();

        int height = (int) this.getPrefWidth();
        int width = (int) this.getPrefWidth();

        int cellHeight = height / Reversi.SIZE;
        int cellWidth = width / Reversi.SIZE;

        GUIPlayer player1 = new GUIPlayer(this, 0, this.board, cellHeight, cellWidth);
        GUIPlayer player2 = new GUIPlayer(this, 1, this.board, cellHeight, cellWidth);
        for (int i = 0; i < this.board.getSize(); i++) {
            for (int j = 0; j < this.board.getSize(); j++) {
                Rectangle rect = new Rectangle(cellWidth, cellHeight, Color.BLUE);
                rect.setStroke(Color.BLACK);
                this.add(rect, j, i);
                if (this.board.getCell(i, j).getSymbol() == 0) {
                    player1.draw(j, i);
                } else if (this.board.getCell(i, j).getSymbol() == 1) {
                    player2.draw(j, i);
                }
            }
        }
    }
}
