import javafx.fxml.FXMLLoader;
import javafx.scene.layout.GridPane;

import java.io.IOException;

public class Display extends GridPane {
    private Board board;

    public Display(Board board) throws IOException {

        this.board = board;
        GridPane drawingBoard = (GridPane) FXMLLoader.load(getClass().getResource("BoardXML.fxml"));
        FXMLLoader fxmlLoader = new
                FXMLLoader(getClass().getResource("BoardXML.fxml"));

        StartScreenController.primaryStage.getScene().setRoot(drawingBoard);
        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
    }

    public void draw() {
        int size = 8;
        for (int i = 0; i < this.board.getSize(); i++) {
            for (int j = 0; j < this.board.getSize(); j++) {
                if (this.board.getCell(i, j).isEmpty()) {
//                    this.add(new Rectangle(this.getWidth() / size, this.getHeight() / size, Color.WHITE), j, i);
                } else {
//                    this.add(new Rectangle(this.getWidth() / size, this.getHeight() / size, Color.BLACK), j, i);
                }
            }
        }
    }
}