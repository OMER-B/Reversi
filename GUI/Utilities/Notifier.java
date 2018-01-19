package GUI.Utilities;

public interface Notifier {
    /**
     * Adds a listener.
     *
     * @param listener listener to add.
     */
    void addListener(Listener listener);

    /**
     * Notifies the listener.
     */
    void notifyListener();
}
