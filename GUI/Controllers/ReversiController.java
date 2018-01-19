package GUI.Controllers;

import GUI.GUIGameInfo;
import GUI.Listeners.ScoreListener;
import GUI.Listeners.UIListener;
import GUI.Reversi;
import GUI.Utilities.Listener;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ResourceBundle;

public class ReversiController implements Initializable {

    @FXML
    private VBox root;

    @FXML
    private Label blackScore = new Label();

    @FXML
    private Label whiteScore = new Label();

    @FXML
    private Label currentPlayer;

    private GUIBoard GUIBoard;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        setup();
        this.GUIBoard.setPrefWidth(Reversi.BOARD_WIDTH);
        this.GUIBoard.setPrefHeight(Reversi.BOARD_HEIGHT);

        this.GUIBoard.init();
        this.root.widthProperty().addListener((observable, oldValue, newValue) -> {
            this.GUIBoard.setPrefWidth(newValue.doubleValue());
            this.GUIBoard.draw();
        });
        this.root.heightProperty().addListener((observable, oldValue, newValue) -> {

            this.GUIBoard.setPrefHeight(newValue.doubleValue() - 20);
            this.GUIBoard.draw();
        });
        this.root.getChildren().add(1, this.GUIBoard);
    }

    /**
     * Sets up the game.
     */
    private void setup() {
        Settings settings = new Settings();
        settings.load();
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        gameInfo.setGame();

        setupListeners();
        this.GUIBoard = gameInfo.getBoard();
    }

    /**
     * Sets up the listeners.
     */
    private void setupListeners() {
        Listener blackListener = new ScoreListener(this.blackScore);
        Listener whiteListener = new ScoreListener(this.whiteScore);
        Listener turnListener = new UIListener(this.currentPlayer);
        GUIGameInfo.getInstance().getGame().addListener(turnListener);
        GUIGameInfo.getInstance().getGUIPlayers()[0].addListener(blackListener);
        GUIGameInfo.getInstance().getGUIPlayers()[1].addListener(whiteListener);
    }

    /**
     * Settings menu.
     */
    @FXML
    protected void settings() {
        try {
            Stage stage = new Stage();
            Pane root = (Pane) FXMLLoader.load(getClass().getClassLoader().getResource("FXMLs/Settings.fxml"));
            Scene scene = new Scene(root, Reversi.SETTINGS_SIZE, Reversi.SETTINGS_SIZE);
            scene.getStylesheets().add(getClass().getClassLoader().getResource("Resources/StyleSheet.css").toExternalForm());
            stage.setTitle("S");
            stage.setMinHeight(Reversi.SETTINGS_SIZE);
            stage.setMinWidth(Reversi.SETTINGS_SIZE);
            stage.setMaxWidth(Reversi.SETTINGS_SIZE);
            stage.setMaxHeight(Reversi.SETTINGS_SIZE);
            stage.setScene(scene);
            stage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Closes the window.
     */
    @FXML
    protected void close() {
        Stage stage = (Stage) this.root.getScene().getWindow();
        stage.close();
    }
}