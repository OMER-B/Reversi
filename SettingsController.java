import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.Pane;

import java.io.*;

public class SettingsController {
    private SettingsInfo settings;
    private static final String SETTINGS_FILE = "settings";

    @FXML
    private Slider sizeSlider;
    @FXML
    private ToggleGroup firstPlayer;

    @FXML
    protected void resume() throws IOException {
        System.out.println("TOGGLED: " + ((RadioButton) firstPlayer.getSelectedToggle()).getText());
        System.out.println("SLIDER: " + sizeSlider.getValue());
        File settingsFile = new File(SETTINGS_FILE);
        save(settingsFile);
        Pane welcome = (Pane) FXMLLoader.load(getClass().getResource("StartScreen.fxml"));
        FXMLLoader fxmlLoader = new
                FXMLLoader(getClass().getResource("StartScreen.fxml"));

        StartScreenController.primaryStage.getScene().setRoot(welcome);
        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }


    /**
     * Save table data to the specified file.
     *
     * @param filename file
     * @throws IOException io exception
     */
    public void save(File filename) throws IOException {
        ObjectOutputStream oos = null;
        try {
            oos = new ObjectOutputStream(new FileOutputStream(filename));
            oos.writeObject(this.settings);
        } catch (IOException e) {
            System.err.println("Something went wrong while writing settings file.");
            e.printStackTrace();
        } finally {
            try {
                if (oos != null) {
                    oos.close();
                }
            } catch (IOException e) {
                System.err.println("Failed closing the file after saving.");
                e.printStackTrace();
            }
        }
    }

    /**
     * Load table data from file. Current table data is cleared.
     *
     * @param filename file
     * @throws IOException io exception
     */
    public void load(File filename) throws IOException {
        ObjectInputStream ois = null;
        try {
            ois = new ObjectInputStream(new FileInputStream(filename));
            this.settings = (SettingsInfo) ois.readObject();
        } catch (Exception e) {
            System.err.println("Error while loading file.");
            e.printStackTrace();
        } finally {
            try {
                if (ois != null) {
                    ois.close();
                }
            } catch (IOException e) {
                System.err.println("Failed closing the file after loading.");
                e.printStackTrace();
            }
        }
    }
}
