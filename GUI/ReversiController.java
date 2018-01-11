package GUI;

import Console.Board;
import Console.Gameflow;
import Console.Player;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.net.URL;
import java.util.ResourceBundle;

public class ReversiController implements Initializable {

    @FXML
    private VBox root;

    private GUIBoard ReversiGUIBoard;

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        Player[] players = {
                new Player(0), new Player(1)
        };
        this.ReversiGUIBoard = new GUIBoard(new Board(Reversi.SIZE, players));
        this.ReversiGUIBoard.setPrefWidth(Reversi.WIDTH);
        this.ReversiGUIBoard.setPrefHeight(Reversi.HEIGHT);
        this.root.getChildren().add(1,this.ReversiGUIBoard);
        this.ReversiGUIBoard.draw();
        this.root.widthProperty().addListener((observable, oldValue, newValue) -> {
            double boardNewWidth = newValue.doubleValue();
            this.ReversiGUIBoard.setPrefWidth(boardNewWidth);
            this.ReversiGUIBoard.draw();
        });
        this.root.heightProperty().addListener((observable, oldValue, newValue) -> {
            this.ReversiGUIBoard.setPrefHeight(newValue.doubleValue()-70);
            this.ReversiGUIBoard.draw();
        });
    }

    @FXML
    protected void start() {
        Player[] players = {new Player(0), new Player(1)};
//        Gameflow game = new Gameflow(players, this.ReversiGUIBoard, Reversi.SIZE);
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
