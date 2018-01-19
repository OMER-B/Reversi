package GUI.Utilities;

import javafx.scene.paint.Color;

import java.io.Serializable;

public class SettingsInfo implements Serializable {
    private static SettingsInfo ourInstance = new SettingsInfo();
    private int size, first;
    private Color black, white;

    /**
     * Constructor for SettingsInfo. defaulted.
     */
    private SettingsInfo() {
        this.size = 8;
        this.first = 0;
        this.black = Color.BLACK;
        this.white = Color.WHITE;
    }

    /**
     * Returns the singleton.
     *
     * @return instance of the singleton.
     */
    public static SettingsInfo getInstance() {
        return ourInstance;
    }

    /**
     * Returns size of the board.
     *
     * @return size of the board.
     */
    public int getSize() {
        return size;
    }

    /**
     * Sets size of the board.
     *
     * @param size size of the board.
     */
    public void setSize(int size) {
        this.size = size;
    }

    /**
     * Returns starting player's index.
     *
     * @return starting player index.
     */
    public int getFirst() {
        return first;
    }

    /**
     * Sets first player.
     *
     * @param first first player's index.
     */
    public void setFirst(int first) {
        this.first = first;
    }

    /**
     * Returns black player's color.
     *
     * @return Color of black player.
     */
    public Color getBlack() {
        return black;
    }

    /**
     * Sets black player color.
     *
     * @param black Color of black player.
     */
    public void setBlack(Color black) {
        this.black = black;
    }

    /**
     * Returns white player's color.
     *
     * @return Color of white player.
     */
    public Color getWhite() {
        return white;
    }

    /**
     * Sets white player color.
     *
     * @param white Color of white player.
     */
    public void setWhite(Color white) {
        this.white = white;
    }
}
