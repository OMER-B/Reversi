package GUI;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Reversi extends Application {
    public static final int BOARD_HEIGHT = 560;
    public static final int BOARD_WIDTH = 600;
    public static final int SCREEN_SIZE = 600;
    public static final int SETTINGS_SIZE = 420;

    /**
     * Main
     *
     * @param args Empty.
     */
    public static void main(String[] args) {
        launch(args);
    }

    /**
     * Starting.
     *
     * @param primaryStage Stage.
     */
    @Override
    public void start(Stage primaryStage) {
        try {
            VBox root = (VBox) FXMLLoader.load(getClass().getClassLoader().getResource("FXMLs/Reversi.fxml"));
            Scene scene = new Scene(root, SCREEN_SIZE, SCREEN_SIZE);
            scene.getStylesheets().add(getClass().getClassLoader().getResource("Resources/StyleSheet.css").toExternalForm());
            primaryStage.setTitle("R");
            primaryStage.setScene(scene);
            primaryStage.setMinWidth(scene.getWidth());
            primaryStage.setMinHeight(scene.getHeight());
//            primaryStage.setMaxWidth(scene.getWidth());
//            primaryStage.setMaxHeight(scene.getHeight());
            primaryStage.show();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
