package GUI;

import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;

public class GUIDisk extends Circle {

    private int i;
    private int j;


    /**
     * Constructor for GUIDisks. Easier to draw.
     *
     * @param radius radius of the disk
     * @param fill   fill color of the disk.
     * @param i      i position of the disk.
     * @param j      j position of the disk.
     */
    public GUIDisk(double radius, Paint fill, int i, int j) {
        super(radius, fill);
        this.i = i;
        this.j = j;
    }
}
