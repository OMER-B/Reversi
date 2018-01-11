package Console;

import java.util.Vector;

abstract public class Logic {
    public Vector<Point> getPlayerCell(Board board, Player player) {
        Vector<Point> playerCells = new Vector<Point>();
        int boardSize = board.getSize();
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (board.getPlayer(i, j) != null) {
                    if (board.getPlayer(i, j) == player) {
                        playerCells.add(new Point(i, j));
                    }
                }
            }
        }
        return playerCells;
    }

    abstract public Vector<Point> getOptionalMoves(Board board, Player player);

    abstract public void putNewCell(Board board, Player player, Point newCell);

    public boolean isOptionInList(Point newOption, Vector<Point> Options) {
        for (Point option : Options) {
            if ((option.getX() == newOption.getX()) && (option.getY() == newOption.getY())) {
                return true;
            }
        }
        return false;
    }

    public Player findRival(Player currentPlayer, Board board) {
        int boardSize = board.getSize();
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if ((!board.getCell(i, j).isEmpty())
                        && (board.getPlayer(i, j) != currentPlayer)) {
                    return board.getPlayer(i, j);
                }
            }
        }
        return null;
    }

    public Player getWinner(Player[] players) {
        return players[0].getScore() == players[1].getScore() ? players[0] : players[1];
    }

    public boolean isEnemy(Player player1, Player player2) {
        return player2.getSymbol() != 0 && player2.getSymbol() != 0 && player1 != player2;
    }
}