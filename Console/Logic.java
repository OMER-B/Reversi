package Console;

import java.util.Vector;

import static Console.Symbol.EMPTY;

abstract public class Logic {
    /**
     * Returns all cells of the player.
     *
     * @param board  Board to get cells from.
     * @param player Player of desired cells.
     * @return Vector of points of the player's positions.
     */
    public Vector<Point> getPlayerCell(Board board, Player player) {
        Vector<Point> playerCells = new Vector<Point>();
        int boardSize = board.getSize();
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                if (!board.getCell(i, j).isEmpty()) {
                    if (board.getCell(i, j).getSymbol() == player.getSymbol()) {
                        playerCells.add(new Point(i, j));
                    }
                }
            }
        }
        return playerCells;
    }

    /**
     * Returns possible moves of the player.
     *
     * @param board  Board to get the moves on.
     * @param player Player whose moves are wanted
     * @return Vector of points of the optional moves for the player.
     */
    abstract public Vector<Point> getOptionalMoves(Board board, Player player);

    /**
     * Puts a new cell on the board.
     *
     * @param board   Board to put the cell on.
     * @param player  Player whose cell to put
     * @param newCell Cell to put.
     */
    abstract public void putNewCell(Board board, Player player, Point newCell);

    /**
     * Checks if given point is in the vector.
     *
     * @param newOption Point to find.
     * @param Options   Vector of points.
     * @return true if point in vector, false otherwise.
     */
    public boolean isOptionInList(Point newOption, Vector<Point> Options) {
        for (Point option : Options) {
            if ((option.getX() == newOption.getX()) && (option.getY() == newOption.getY())) {
                return true;
            }
        }
        return false;
    }


    /**
     * Returns the winner of the game.
     *
     * @param players Array of players to get winner from.
     * @return int index of the winning player in the array.
     */
    public int getWinner(Player[] players) {
        return players[0].getScore() > players[1].getScore() ? 0 : 1;
    }

    /**
     * Checks if two players are enemies.
     *
     * @param player1 first player.
     * @param player2 second player.
     * @return true if players are enemies, false otherwise.
     */
    public boolean isEnemy(Player player1, Player player2) {
        return (player2.getSymbol() != EMPTY) && (player2.getSymbol() != EMPTY)
                && (player1.getSymbol() != player2.getSymbol());
    }
}