import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.Pane;

import java.io.*;
import java.net.URL;
import java.util.ResourceBundle;

public class SettingsController implements Initializable {
    private SettingsInfo settings = new SettingsInfo();
    private static final String SETTINGS_FILE = "settings";

    @FXML
    private Slider sizeSlider;
    @FXML
    private ToggleGroup firstPlayer;

    @FXML
    private RadioButton black;
    @FXML
    private RadioButton white;

    @FXML
    protected void resume() throws IOException {
        setNewSettings();
        Pane welcome = (Pane) FXMLLoader.load(getClass().getResource("StartScreen.fxml"));
        StartScreenController.primaryStage.getScene().setRoot(welcome);
    }

    @FXML
    protected void reset() {
        settings.setSize(8);
        settings.setFirst(0);
        getNewSettings();
    }

    public void setNewSettings() throws IOException {


        File settingsFile = new File(SETTINGS_FILE);

        settings.setSize((int) sizeSlider.getValue());
        if (black.isSelected()) {
            settings.setFirst(0);
        } else {
            settings.setFirst(1);
        }
        save(settingsFile);
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

    public void getNewSettings() {
        if (this.settings.getFirst() == 1) {
            this.firstPlayer.selectToggle(this.white);
        } else {
            this.firstPlayer.selectToggle(this.black);
        }
        this.sizeSlider.setValue(this.settings.getSize());
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
            getNewSettings();
        } catch (Exception e) { // File does not exist.
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

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        File settingsFile = new File(SETTINGS_FILE);
        try {
            load(settingsFile);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
