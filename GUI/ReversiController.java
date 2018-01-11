package GUI;

import Console.ConsoleGameInfo;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ResourceBundle;

public class ReversiController implements Initializable {

    @FXML
    private VBox root;

    private GUIBoard GUIBoard;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        ConsoleGameInfo console = ConsoleGameInfo.getInstance();
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        this.GUIBoard = gameInfo.getBoard();
        this.GUIBoard.setPrefWidth(Reversi.WIDTH);
        this.GUIBoard.setPrefHeight(Reversi.HEIGHT);
        this.root.getChildren().add(1, this.GUIBoard);
        this.GUIBoard.draw();
        this.root.widthProperty().addListener((observable, oldValue, newValue) -> {
            double boardNewWidth = newValue.doubleValue();
            this.GUIBoard.setPrefWidth(boardNewWidth);
            this.GUIBoard.draw();
        });
        this.root.heightProperty().addListener((observable, oldValue, newValue) -> {
            this.GUIBoard.setPrefHeight(newValue.doubleValue() - 70);
            this.GUIBoard.draw();
        });
    }

    @FXML
    protected void start() {
    }

    @FXML
    protected void settings() {
    }

    @FXML
    protected void close() {
        Stage stage = (Stage) this.root.getScene().getWindow();
        stage.close();
    }
}
