package GUI;

import Console.Player;
import Console.Symbol;
import GUI.Controllers.GUIBoard;
import GUI.Utilities.Listener;
import GUI.Utilities.Notifier;
import GUI.Utilities.SettingsInfo;
import javafx.geometry.HPos;
import javafx.geometry.VPos;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;

import java.util.ArrayList;
import java.util.List;

public class GUIPlayer implements Notifier {
    private Player player;
    private GUIBoard board;
    private Color color;
    private Listener listener;
    private List<GUIDisk> disks;

    /**
     * Constructor for GUIPlayer.
     *
     * @param player Player to wrap.
     */
    public GUIPlayer(Player player) {
        this.player = player;
        this.color = SettingsInfo.getInstance().getWhite();
        if (this.player.getSymbol() == Symbol.BLACK) {
            this.color = SettingsInfo.getInstance().getBlack();
        }
        this.disks = new ArrayList<>();
    }

    /**
     * Draws the player.
     *
     * @param i      position i of the board to draw.
     * @param j      position j of the board to draw.
     * @param width  width of the player.
     * @param height height of the player.
     */
    public void draw(int i, int j, double width, double height) {
        this.board = GUIGameInfo.getInstance().getBoard();
        double radius = Math.min(width / 2, height / 2);
        GUIDisk newDisk = new GUIDisk(radius, this.color.darker(), i, j);
        GUIDisk newDisk2 = new GUIDisk(radius * 0.85, this.color, i, j);
        this.disks.add(newDisk);
        this.disks.add(newDisk2);
        GridPane.setHalignment(newDisk, HPos.CENTER);
        GridPane.setValignment(newDisk2, VPos.TOP);
        GridPane.setHalignment(newDisk2, HPos.CENTER);
        this.board.add(newDisk, i, j);
        this.board.add(newDisk2, i, j);
    }

    /**
     * Returns a list of all the players disks.
     *
     * @return List of the players disks.
     */
    public List<GUIDisk> getDisks() {
        return disks;
    }

    /**
     * Returns the color of the player.
     *
     * @return Color of the player.
     */
    public Color getColor() {
        return color;
    }

    /**
     * Returns the wrapper player.
     *
     * @return Player wrapped by the GUIPlayer.
     */
    public Player getPlayer() {
        return this.player;
    }

    /**
     * Sets the score of the player.
     *
     * @param score new score to set.
     */
    public void setScore(int score) {
        this.player.setScore(score);
    }

    @Override
    public void addListener(Listener listener) {
        this.listener = listener;
    }

    @Override
    public void notifyListener() {
        this.listener.notifyGame(this);
    }
}
