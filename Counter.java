public class Counter {
    private int value;

    public Counter() {
        this.value = 0;
    }

    public Counter(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    public void setValue(int newVal) {
        this.value = newVal;
    }

    public void increaseCounter() {
        this.value++;
    }

    public void decreaseCounter() {
        this.value--;
    }
}