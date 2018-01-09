import javafx.scene.layout.GridPane;

import java.io.IOException;

public class Reversi {
    public void run() throws IOException {
        SettingsInfo settings = new SettingsInfo();
        settings.setFirst(0);
        settings.setSize(8);
        Gameflow game = new Gameflow(settings.getSize(), settings.getFirst());
//        game.run();
    }
}
