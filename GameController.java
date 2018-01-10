import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class GameController implements Initializable {

    @FXML
    private VBox root;

    private Gameflow game;

    private Board board;

    public GameController() throws IOException {
        root = new VBox();
        SettingsInfo settings = new SettingsInfo();
        settings.setFirst(0);
        settings.setSize(8);

        Player players[] = new Player[2];
        players[settings.getFirst()] = new Player(new Disk('X'));
        players[1 - settings.getFirst()] = new Player(new Disk('O'));
        board = new Board(settings.getSize(), players);

        game = new Gameflow(board, players);
        System.out.println("finished game controller constructor");
    }

    public void run() throws IOException {
        game.run();
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        BoardController bc = new BoardController();
        bc.setBoard(board);
        bc.setPrefWidth(400);
        bc.setPrefHeight(400);
        root.getChildren().add(0, bc);
        System.out.println("finished game controller Initialize");
        Scene scene = new Scene(root, 600, 400);
        StartScreenController.primaryStage.setScene(scene);
        System.out.println("finished creating board in game controller initialize");
        bc.draw();
    }
}
