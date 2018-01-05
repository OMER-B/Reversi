import java.util.Vector;

abstract public class Logic {
    public Vector<Point> getPlayerCell(Board board, Player player) {
        Vector<Point> playerCells = new Vector<Point>();
        int x = board.getWidth();
        int y = board.getHeight();
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
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
        int x = board.getWidth();
        int y = board.getHeight();
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                if ((!board.getCell(i, j).isEmpty())
                        && (board.getPlayer(i, j) != currentPlayer)) {
                    return board.getPlayer(i, j);
                }
            }
        }
        return null;
    }

    public Player getWinner(Player[] players) {
        if (players[0].compare(players[1]) == 1) {
            return players[0];
        }
        return players[1];
    }

    public boolean isEnemy(Player player1, Player player2) {
        if (player2.getSymbol() == 0 || player2.getSymbol() == 0) {
            return false;
        }
        return player1 != player2;
    }
}
