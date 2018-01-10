import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.layout.GridPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

public class BoardController extends GridPane {

    private Board board;

    BoardController(){



        FXMLLoader fxmlLoader = new
                FXMLLoader(getClass().getResource("BoardXML.fxml"));
        fxmlLoader.setRoot(this);
        fxmlLoader.setController(this);
        try {
            fxmlLoader.load();
        } catch (IOException exception) {
            throw new RuntimeException(exception);
        }
        System.out.println("finished board controller constructor");
    }

    public void setBoard(Board board){
        this.board = board;
    }

    public void draw() {
        int size = 8;
        for (int i = 0; i < this.board.getSize(); i++) {
            for (int j = 0; j < this.board.getSize(); j++) {
                if (this.board.getCell(i, j).isEmpty()) {
                    this.add(new Rectangle(this.getWidth() / size, this.getHeight() / size, Color.WHITE), j, i);
                } else if (this.board.getCell(i, j).getSymbol()=='X') {
                    this.add(new Rectangle(this.getWidth() / size, this.getHeight() / size, Color.BLACK), j, i);
                }
                else {
                    this.add(new Rectangle(this.getWidth() / size, this.getHeight() / size, Color.RED), j, i);
                }
            }
        }
    }

}
