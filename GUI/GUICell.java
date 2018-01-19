package GUI;

import Console.Cell;
import Console.Symbol;
import GUI.Controllers.GUIBoard;
import GUI.Utilities.Listener;
import GUI.Utilities.Notifier;
import javafx.geometry.HPos;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

public class GUICell extends Rectangle implements Notifier {
    private Cell cell;
    private GUIBoard GuiBoard;
    private Listener cellListener;
    private GUIPlayer guiPlayer;
    private double cellWidth, cellHeight;
    private Color[] colors = {
            Color.valueOf("#303030"),
            Color.valueOf("#e0e0e0")
    };
    private Color currentColor;
    private GUIDisk disk;
    private double diskRadius;

    /**
     * Constructor for GUICell.
     *
     * @param width  width of the cell.
     * @param height height of the cell.
     * @param cell   cell to wrap.
     */
    public GUICell(double width, double height, Cell cell) {
        super(width, height);
        this.cellWidth = width;
        this.cellHeight = height;
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        this.GuiBoard = gameInfo.getBoard();
        this.cell = cell;
        this.currentColor = this.colors[(this.cell.getX() + this.cell.getY()) % 2];
        this.setFill(this.currentColor);
        this.diskRadius = Math.min(this.cellWidth, this.cellHeight) * 0.4;
        this.disk = new GUIDisk(diskRadius / 2, this.currentColor, cell.getX(), cell.getY());
        this.disk.setMouseTransparent(true);
    }

    /**
     * Returns wrapped cell.
     *
     * @return Cell wrapped cell.
     */
    public Cell getCell() {
        return cell;
    }

    /**
     * Marks the cell in available color.
     *
     * @param player Player's color to set.
     */
    public void markAvailable(GUIPlayer player) {
        try {
            this.disk.setFill(player.getColor());
        } catch (Exception e) {
            this.setFill(Color.TRANSPARENT);
        }
    }

    /**
     * Unmarks the cell as available.
     */
    public void unmarkAvailable() {
        this.disk.setFill(Color.TRANSPARENT);
    }

    /**
     * Draws the cell.
     */
    public void draw() {

        this.GuiBoard.getChildren().remove(this);
        this.GuiBoard.add(this, this.cell.getX(), this.cell.getY());
        this.GuiBoard.getChildren().remove(this.disk);
        this.GuiBoard.add(this.disk, this.cell.getX(), this.cell.getY());
        GridPane.setHalignment(this.disk, HPos.CENTER);
        if (this.cell.getSymbol() != Symbol.EMPTY) {
            this.guiPlayer = GUIGameInfo.getInstance().getGUIPlayers()[this.cell.getSymbol().ordinal()];
            this.guiPlayer.draw(this.cell.getX(), this.cell.getY(), this.cellWidth, this.cellHeight);
            this.guiPlayer.draw(this.cell.getX(), this.cell.getY(), this.cellWidth - 10, this.cellHeight - 10);
        }
    }

    /**
     * Sets the size of the cell.
     *
     * @param width  new cell width.
     * @param height new cell height
     */
    public void setCellSize(double width, double height) {
        super.setWidth(width);
        super.setHeight(height);
        this.cellWidth = width;
        this.cellHeight = height;
        this.diskRadius = Math.min(this.cellWidth, this.cellHeight) * 0.6;
    }

    @Override
    public void addListener(Listener listener) {
        this.cellListener = listener;
    }

    @Override
    public void notifyListener() {
        this.cellListener.notifyGame(this);
    }
}
