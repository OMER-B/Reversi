package GUI;

import Console.Board;
import Console.Logic;
import Console.Player;
import Console.Point;
import javafx.stage.Stage;

import java.util.Vector;

import static java.lang.System.exit;

public class GUIGameflow {
    private Player players[];
    private int currentPlayer;
    private boolean shouldContinue;
    private boolean previousDidNotMakeMove;
    private GUIBoard board;
    private Logic logic;

    public GUIGameflow() {
        GUIGameInfo gameInfo = GUIGameInfo.getInstance();
        this.board = gameInfo.getBoard();
        this.logic = gameInfo.getLogic();
        this.players = gameInfo.getPlayers();
        currentPlayer = 0;
        shouldContinue = true;
        previousDidNotMakeMove = false;
    }

    public void makeMove(Point point) {
        Vector<Point> moves = logic.getOptionalMoves(board.getBoard(),players[currentPlayer]);
        if(moves.isEmpty()){
            if(previousDidNotMakeMove){
                shouldContinue = false;
                Stage stage = (Stage)this.board.getScene().getWindow();
                stage.close();
            }
            previousDidNotMakeMove = true;
            currentPlayer = 1-currentPlayer;
            return;
        }
        for(Point p : moves){
            if(p.getX()==point.getX() && p.getY()==point.getY()){
                logic.putNewCell(board.getBoard(), players[currentPlayer], point);
                currentPlayer = 1-currentPlayer;
                previousDidNotMakeMove = false;
                board.draw();
            }
        }
    }
}