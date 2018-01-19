package GUI;

import Console.Logic;
import Console.Player;
import Console.Point;
import GUI.Controllers.GUIBoard;
import GUI.Utilities.Listener;
import GUI.Utilities.Notifier;
import GUI.Utilities.SettingsInfo;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.shape.Circle;
import javafx.stage.Modality;
import javafx.stage.Stage;

import java.util.Vector;

public class GUIGameflow implements Notifier {
    private Player players[];
    private int currentPlayer;
    private boolean previousDidNotMakeMove;
    private GUIBoard board;
    private Logic logic;
    private int size = SettingsInfo.getInstance().getSize();
    private Listener turnListener;

    /**
     * Constructor for the gameflow.
     */
    public GUIGameflow() {
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        this.board = gameInfo.getBoard();
        this.logic = gameInfo.getLogic();
        this.players = gameInfo.getPlayers();
        currentPlayer = SettingsInfo.getInstance().getFirst();
        previousDidNotMakeMove = false;
    }

    /**
     * Draws the first move of the game.
     */
    public void firstMove() {
        Vector<Point> moves = availableMoves(SettingsInfo.getInstance().getFirst());
        markAvailableCells(SettingsInfo.getInstance().getFirst());
        notifyListener();
    }

    /**
     * Makes a move by click.
     *
     * @param point clicked point.
     */
    public void makeMove(Point point) {
        Vector<Point> moves = availableMoves(currentPlayer);
        boolean shouldContinue = false;
        if (moves.isEmpty()) {
            if (previousDidNotMakeMove) {
                announceWinner();
                Stage stage = (Stage) this.board.getScene().getWindow();
                stage.close();
                return;
            }
            previousDidNotMakeMove = true;
            return;
        }

        for (Point p : moves) {
            if (p.getX() == point.getX() && p.getY() == point.getY()) {
                logic.putNewCell(board.getBoard(), players[currentPlayer], point);
                board.draw();
                shouldContinue = true;
            }
        }

        if (!shouldContinue) {
            return;
        } else {
            previousDidNotMakeMove = false;
        }

        markUnavailable();
        Vector<Point> nextMoves = availableMoves(1 - currentPlayer);
        if (this.board.getBoard().isFull() || (nextMoves.isEmpty() && this.previousDidNotMakeMove)) {
            announceWinner();
            Stage stage = (Stage) this.board.getScene().getWindow();
            stage.close();
            return;
        }
        if (nextMoves.isEmpty()) {
            skipTurn();
            previousDidNotMakeMove = true;
            return;
        }
        currentPlayer = 1 - currentPlayer;
        markAvailableCells(currentPlayer);
        notifyListener();
    }

    /**
     * Pops up the skip turn window.
     */
    private void skipTurn() {
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        GridPane root = new GridPane();
        Label label = new Label("No moves. Skipped turn.");
        root.getChildren().add(label);
        Scene scene = new Scene(root, 200, 100);
        root.setPrefSize(scene.getWidth(), scene.getHeight());
        stage.setScene(scene);
        stage.showAndWait();
        markAvailableCells(currentPlayer);
    }

    /**
     * Pops up the winner window.
     */
    private void announceWinner() {
        Stage stage = new Stage();
        stage.initModality(Modality.APPLICATION_MODAL);
        GridPane root = new GridPane();
        Label label = new Label();
        if (this.players[0].getScore() == this.players[1].getScore()) {
            label.setText("It's a tie!");
            root.getChildren().addAll(label);
        } else {
            int winner = this.logic.getWinner(players);
            String name = "second";
            if (winner == SettingsInfo.getInstance().getFirst()) {
                name = "first";
            }
            Circle circle = new Circle(20, GUIGameInfo.getInstance().getGUIPlayers()[winner].getColor());
            label.setText("Winner is " + name + " player");
            root.getChildren().addAll(circle, label);
        }
        Scene scene = new Scene(root, 200, 100);
        root.setPrefSize(scene.getWidth(), scene.getHeight());
        stage.setScene(scene);
        stage.showAndWait();
    }

    /**
     * Returns list of available moves.
     *
     * @param playerIndex player index to find moves.
     * @return Vector of available moves.
     */
    private Vector<Point> availableMoves(int playerIndex) {
        return logic.getOptionalMoves(board.getBoard(), players[playerIndex]);
    }

    /**
     * Marks the available cells.
     *
     * @param playerIndex player index to mark with its colors.
     */
    public void markAvailableCells(int playerIndex) {
        Vector<Point> moves = availableMoves(playerIndex);
        for (Point point : moves) {
            board.getGUICell(point).markAvailable(GUIGameInfo.getInstance().getGUIPlayers()[playerIndex]);
        }
    }

    /**
     * Unmarks the cells.
     */
    private void markUnavailable() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board.getGUICell(i, j).unmarkAvailable();
            }
        }
    }

    @Override
    public void addListener(Listener listener) {
        this.turnListener = listener;
    }

    @Override
    public void notifyListener() {
        this.turnListener.notifyGame(GUIGameInfo.getInstance().getGUIPlayers()[currentPlayer]);
    }
}