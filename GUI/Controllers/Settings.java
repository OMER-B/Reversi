package GUI.Controllers;

import GUI.Utilities.SettingsInfo;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ColorPicker;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Slider;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

import java.io.File;
import java.net.URL;
import java.util.Formatter;
import java.util.ResourceBundle;
import java.util.Scanner;

public class Settings implements Initializable {
    private static final String SETTINGS_FILE = "config";

    @FXML
    private Slider sizeSlider;

    @FXML
    private ToggleGroup firstPlayer;

    @FXML
    private RadioButton black;

    @FXML
    private RadioButton white;

    @FXML
    private GridPane root;

    @FXML
    private ColorPicker blackColor;

    @FXML
    private ColorPicker whiteColor;

    private File file = new File(SETTINGS_FILE);

    private SettingsInfo settingsInfo = SettingsInfo.getInstance();

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        getNewValues();
        try {
            load();
        } catch (Exception e) {
            reset();
        }
    }

    /**
     * Resets the settings.
     */
    @FXML
    protected void reset() {
        settingsInfo.setSize(8);
        settingsInfo.setFirst(0);
        settingsInfo.setBlack(Color.BLACK);
        settingsInfo.setWhite(Color.WHITE);
        getNewValues();
    }

    /**
     * Closes the menu.
     */
    @FXML
    protected void cancel() {
        Stage stage = (Stage) this.root.getScene().getWindow();
        stage.close();
    }

    /**
     * Accepts new settings.
     */
    @FXML
    protected void accept() {
        setNewValues();
        try {
            save();
        } catch (Exception e) {
            reset();
        }
        try {
            Stage stage = (Stage) this.root.getScene().getWindow();
            stage.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Load data from file. Current data is cleared.
     */
    public void load() {
        try {
            Scanner scanner = new Scanner(this.file);
            String[] reader = new String[4];
            int i = 0;
            while (scanner.hasNext()) {
                reader[i] = scanner.next();
                i++;
            }
            settingsInfo.setSize(Integer.parseInt(reader[0]));
            settingsInfo.setFirst(Integer.parseInt(reader[1]));
            settingsInfo.setBlack(Color.valueOf(reader[2]));
            settingsInfo.setWhite(Color.valueOf(reader[3]));
        } catch (Exception e) {
        }
    }

    /**
     * Sets the new values.
     */
    public void setNewValues() {
        settingsInfo.setSize((int) sizeSlider.getValue());
        if (black.isSelected()) {
            settingsInfo.setFirst(0);
        } else {
            settingsInfo.setFirst(1);
        }
        settingsInfo.setWhite(whiteColor.getValue());
        settingsInfo.setBlack(blackColor.getValue());
    }

    /**
     * Gets the new values.
     */
    public void getNewValues() {
        if (this.settingsInfo.getFirst() == 1) {
            this.firstPlayer.selectToggle(this.white);
        } else {
            this.firstPlayer.selectToggle(this.black);
        }
        this.sizeSlider.setValue(this.settingsInfo.getSize());
        this.blackColor.setValue(this.settingsInfo.getBlack());
        this.whiteColor.setValue(this.settingsInfo.getWhite());
    }

    /**
     * Save table data to the specified file.
     */
    public void save() {
        try {
            Formatter y = new Formatter("config");
            y.format("%s\n%s\n%s\n%s\n",
                    String.valueOf(settingsInfo.getSize()),
                    String.valueOf(settingsInfo.getFirst()),
                    String.valueOf(settingsInfo.getBlack()),
                    String.valueOf(settingsInfo.getWhite()));
            y.close();
        } catch (Exception e) {

        }
    }

}