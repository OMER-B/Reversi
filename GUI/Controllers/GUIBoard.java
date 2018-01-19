package GUI.Controllers;

import Console.Board;
import Console.ConsoleGameInfo;
import Console.Point;
import Console.Symbol;
import GUI.GUICell;
import GUI.GUIDisk;
import GUI.GUIGameInfo;
import GUI.GUIPlayer;
import GUI.Utilities.SettingsInfo;
import javafx.fxml.FXMLLoader;
import javafx.scene.layout.GridPane;

import java.util.List;

public class GUIBoard extends GridPane {

    private Board board;
    private GUICell GuiCells[][];
    private int size = SettingsInfo.getInstance().getSize();

    /**
     * Constructor for GUIBoard.
     */
    public GUIBoard() {
        ConsoleGameInfo gameInfo = ConsoleGameInfo.getInstance();
        this.board = gameInfo.getBoard();
        this.GuiCells = new GUICell[this.size][this.size];
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getClassLoader().getResource("FXMLs/Board.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
    }

    /**
     * Initializes the cells of the board.
     */
    public void init() {
        int cellWidth = (int) (this.getPrefWidth() / this.size);
        int cellHeight = (int) (this.getPrefHeight() / this.size);

        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                this.GuiCells[i][j] = new GUICell(cellWidth, cellHeight, this.board.getCell(i, j));
                GUICell cell = GuiCells[i][j];
                cell.addListener(GUIGameInfo.getInstance().getListener());
                cell.setOnMouseClicked((event -> cell.notifyListener()));
                this.GuiCells[i][j].draw();
            }
        }
        GUIGameInfo.getInstance().getGame().firstMove();
        updateScores();
    }

    /**
     * Returns the console board.
     *
     * @return Board board of the GUIBoard.
     */
    public Board getBoard() {
        return this.board;
    }

    /**
     * Returns the size of the board.
     *
     * @return size of the board.
     */
    public int getSize() {
        return this.board.getSize();
    }

    /**
     * Draws the board.
     */
    public void draw() {
        clearBoard();

        int cellWidth = (int) (this.getPrefWidth() / this.size);
        int cellHeight = (int) (this.getPrefHeight() / this.size);


        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                this.GuiCells[i][j].setCellSize(cellWidth, cellHeight);
                this.GuiCells[i][j].draw();
            }
        }
        updateScores();
    }

    /**
     * Updates scores of the players.
     */
    private void updateScores() {
        int counter1 = 0, counter2 = 0;
        for (int i = 0; i < this.size; i++) {
            for (int j = 0; j < this.size; j++) {
                if (this.GuiCells[i][j].getCell().getSymbol() == Symbol.BLACK) {
                    counter1++;
                }
                if (this.GuiCells[i][j].getCell().getSymbol() == Symbol.WHITE) {
                    counter2++;
                }
            }
        }
        GUIGameInfo.getInstance().getGUIPlayers()[0].setScore(counter1);
        GUIGameInfo.getInstance().getGUIPlayers()[1].setScore(counter2);

        GUIGameInfo.getInstance().getGUIPlayers()[0].notifyListener();
        GUIGameInfo.getInstance().getGUIPlayers()[1].notifyListener();
    }

    /**
     * Clears the board from everything.
     */
    private void clearBoard() {
        GUIPlayer[] players = GUIGameInfo.getInstance().getGUIPlayers();
        for (int i = 0; i < players.length; i++) {
            List<GUIDisk> disks = GUIGameInfo.getInstance().getGUIPlayers()[i].getDisks();
            for (GUIDisk d : disks) {
                getChildren().remove(d);
            }
            disks.clear();
        }
    }

    /**
     * Returns GUI cell by i, j.
     *
     * @param i i location of the cell.
     * @param j j location of the cell.
     * @return GUICell in position [i][j].
     */
    public GUICell getGUICell(int i, int j) {
        return this.GuiCells[i][j];
    }

    /**
     * Returns GUICell by point.
     *
     * @param point point location of the cell.
     * @return GUICell in point's position.
     */
    public GUICell getGUICell(Point point) {
        return this.GuiCells[point.getX()][point.getY()];
    }
}
