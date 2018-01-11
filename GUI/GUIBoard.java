package GUI;

import Console.Board;
import Console.Cell;
import Console.ConsoleGameInfo;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;

import static Console.Symbol.BLACK;
import static Console.Symbol.WHITE;

public class GUIBoard extends GridPane {

    private Board board;

    private GUIPlayer[] players;

    public GUIBoard() {
        ConsoleGameInfo gameInfo = ConsoleGameInfo.getInstance();
        this.board = gameInfo.getBoard();
    }

    public void addPlayers(GUIPlayer[] players) {
        this.players = players;
    }

    public int getSize() {
        return this.board.getSize();
    }

    public void draw() {

        this.getChildren().clear();

        int height = (int) this.getPrefWidth();
        int width = (int) this.getPrefWidth();

        int cellHeight = height / Reversi.SIZE;
        int cellWidth = width / Reversi.SIZE;

        for (int i = 0; i < this.board.getSize(); i++) {
            for (int j = 0; j < this.board.getSize(); j++) {
                GUICell cell = new GUICell(cellWidth, cellHeight, Color.FUCHSIA, this.board.getCell(i, j));
                cell.draw();
            }
        }
    }

    public Cell getCell(int i, int j) {
        return this.board.getCell(i, j);
    }
}
