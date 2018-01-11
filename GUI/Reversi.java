package GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Reversi extends Application {
    public static final int WIDTH = 530;
    public static final int HEIGHT = 600;
    public static final int SIZE = 8;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        try {
            VBox root = (VBox) FXMLLoader.load(getClass().getResource("FXMLs/Reversi.fxml"));
            Scene scene = new Scene(root, WIDTH, HEIGHT);
            scene.getStylesheets().add(getClass().getResource("StyleSheet.css").toExternalForm());
            primaryStage.setTitle("Maze game");
            primaryStage.setScene(scene);
            primaryStage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
