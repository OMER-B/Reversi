package Console;

public class Counter {
    private int value;

    /**
     * Constructor for counter with input initialized value.
     *
     * @param value
     */
    public Counter(int value) {
        this.value = value;
    }

    /**
     * Returns the current value of the counter.
     *
     * @return value of the counter.
     */
    public int getValue() {
        return this.value;
    }

    /**
     * Sets the value of the counter.
     *
     * @param value new value to set.
     */
    public void setValue(int value) {
        this.value = value;
    }

    /**
     * Increases the counter by 1.
     */
    public void increaseCounter() {
        this.value++;
    }

    /**
     * Decreases the counter by 1.
     */
    public void decreaseCounter() {
        this.value--;
    }
}