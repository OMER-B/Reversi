import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;

import static java.lang.System.exit;

public class StartScreenController extends Application {

    @FXML
    public static Stage primaryStage;

    @Override
    public void start(Stage primaryStage) {
        StartScreenController.primaryStage = primaryStage;
        try {
            welcome();
            StartScreenController.primaryStage.setTitle("REVERSI");
            StartScreenController.primaryStage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }

    protected void welcome() throws IOException {
        Pane welcome = (Pane) FXMLLoader.load(getClass().getResource("StartScreen.fxml"));
        Scene scene = new Scene(welcome, 600, 400);
        scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
        primaryStage.setScene(scene);
    }

    @FXML
    protected void close() {
        exit(0);
    }

    @FXML
    protected void settings() throws IOException {
        Pane settings = (Pane) FXMLLoader.load(getClass().getResource("Settings.fxml"));
        primaryStage.getScene().setRoot(settings);
    }

    public void goToStart() {
        start(primaryStage);
    }

    @FXML
    protected void startGame() throws IOException {
        VBox root = (VBox)FXMLLoader.load(getClass().getResource("GameFXML.fxml"));

        //gameController.run();
    }
}
