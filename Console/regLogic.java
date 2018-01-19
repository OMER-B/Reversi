package Console;

import java.util.Vector;

public class regLogic extends Logic {

    /**
     * Returns optional moves of the player.
     *
     * @param board  Board to get the moves on.
     * @param player Player whose moves are wanted
     * @return Vector of optional moves for the player.
     */
    public Vector<Point> getOptionalMoves(Board board, Player player) {
        Vector<Point> playerCells = super.getPlayerCell(board, player);
        Vector<Point> options = new Vector<>();
        Point option = new Point(-1, -1);

        // For each of the player's cell, check a path for all 8 directions.
        for (int c = 0; c < playerCells.size(); c++) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if ((i != 0) || (j != 0)) {
                        option = checkPath(board, player, playerCells.elementAt(c), i, j);

                        // Checks if the new cells are in boundaries,
                        // because option may include (-1, -1) cells.
                        if (board.inBoundaries(option) && !isOptionInList(option, options)) {
                            // If the move is valid, and not already in the moves list, add it.
                            options.add(option);

                        }
                    }
                }
            }
        }
        return options;
    }

    /**
     * Checks if a path is valid for flip.
     *
     * @param board   Board to put the cells on.
     * @param player  Player to fill the cell with.
     * @param point   Point of the cell.
     * @param xChange x direction of the flippings.
     * @param yChange y direction of the flippings.
     * @return Point to flip.
     */
    public Point checkPath(Board board, Player player, Point point, int xChange, int yChange) {
        boolean passedAtLeastOneRival = false;
        int x = point.getX() + xChange, y = point.getY() + yChange;
        // While the cell being checked is in the board.
        while ((x >= 0) && (x < board.getSize()) && (y >= 0) && (y < board.getSize())) {
            if (player.getSymbol() == board.getCell(x, y).getSymbol()) {
                // If the cell already belongs to the player, return an "empty" cell.
                return new Point(-1, -1);
            }
            if (board.getCell(x, y).getSymbol() != Symbol.EMPTY) {
                // If the cell belongs to the rival continue checking the path in the same direction.
                passedAtLeastOneRival = true;
                x += xChange;
                y += yChange;
            } else if (board.getCell(x, y).getSymbol() == Symbol.EMPTY) {
                // If the cell is empty and we have passed the rival, return that cell.
                if (passedAtLeastOneRival) {
                    return new Point(x, y);
                } else {
                    // If the cell is empty and have not passed the rival, return an empty cell.
                    return new Point(-1, -1);
                }
            }
        }
        return new Point(-1, -1);
    }

    /**
     * Puts a new cell on the board.
     *
     * @param board   Board to put the cell on.
     * @param player  Player whose cell to put
     * @param newCell Cell to put.
     */
    public void putNewCell(Board board, Player player, Point newCell) {
        if ((board.getCell(newCell.getX(), newCell.getY()).getSymbol() != Symbol.EMPTY)
                || (!board.inBoundaries(newCell.getX(), newCell.getY()))) {

            // Console.Cell cannot be put on a non empty cell, or a cell not in the board.
            return;
        }
        Vector<Point> toFlip = new Vector<>();

        // Put the desired cell.
        board.fillCell(newCell, player);
        player.increaseScore();

        // Check all 8 direction for cells neede to be flipped.
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if ((i != 0) || (j != 0)) {
                    Vector<Point> result = checkPathToFlip(board, player, newCell, i, j);

                    for (Point point : result) {
                        if (!isOptionInList(point, toFlip)) {
                            toFlip.add(point);
                        }
                    }
                }
            }
        }
        if (!toFlip.isEmpty()) {
            flipCells(board, toFlip, player);
        }
    }

    /**
     * Returns a path of cells to flip.
     *
     * @param board   Board to flip cells on.
     * @param player  Player to fill the cells with.
     * @param point   Starting point to flip.
     * @param xChange x direction to flip.
     * @param yChange y direction to flip.
     * @return Vector of cells to flip.
     */
    public Vector<Point> checkPathToFlip(Board board, Player player, Point point, int xChange, int yChange) {
        Point toFlip = point;
        Vector<Point> cellsToFlip = new Vector<>();

        // While the cells in the path are inside the board:
        while (board.inBoundaries(toFlip.getX() + xChange, toFlip.getY() + yChange)) {
            int newX = toFlip.getX() + xChange;
            int newY = toFlip.getY() + yChange;
            toFlip = new Point(newX, newY);
            if (board.getCell(newX, newY).getSymbol() == Symbol.EMPTY) {

                // If there is an empty cell in the middle, no cell should be flipped.
                cellsToFlip.clear();
                return cellsToFlip;
            } else if (board.getCell(newX, newY).getSymbol() != player.getSymbol()) {
                // If the cell belongs to the rival add to the list of cells to be flipped.
                cellsToFlip.add(toFlip);
            } else if (board.getCell(newX, newY).getSymbol() == player.getSymbol()) {
                // End of path, return the cells to be flipped.
                return cellsToFlip;
            }
        }
        cellsToFlip.clear();
        return cellsToFlip;
    }

    /**
     * Flips all cells in vector and places new player in them.
     *
     * @param board  Board to flip the cells on.
     * @param cells  Vector of cells to flip.
     * @param player Player to fill the cells with.
     */
    public void flipCells(Board board, Vector<Point> cells, Player player) {
        // Find enemy to update its score.
        Player enemy = null;
        for (Point cell : cells) {
            if (isEnemy(player, board.getPlayer(cell))) {
                enemy = board.getPlayer(cell);
                break;
            }

        }
        // Fill cell with player and update the scores.

        for (Point cell : cells) {
            board.fillCell(cell, player);
            this.updateScore(enemy, player);

        }
    }


    /**
     * Updates the scores of the players.
     *
     * @param prevPlayer original player of the cell.
     * @param currPlayer new player of the cell.
     */
    public void updateScore(Player prevPlayer, Player currPlayer) {
        if (currPlayer.getSymbol().ordinal() != prevPlayer.getSymbol().ordinal()) {
            currPlayer.increaseScore();
            if (prevPlayer.getSymbol() != Symbol.EMPTY) {
                prevPlayer.decreaseScore();
            }
        }
    }
}