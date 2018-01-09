import java.io.Serializable;

public class SettingsInfo implements Serializable {
    private int size;
    private int first = 0;

    public int getSize() {
        return size;
    }

    public int getFirst() {
        return first;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public void setFirst(int first) {
        this.first = first;
    }
}
