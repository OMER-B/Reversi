#include "regLogic.h"
#include <climits>

vector<Point> RegLogic::getOptionalMoves(Board &board, const Player &player) {
  vector<Point> playerCells = getPlayerCells(board, player);
  vector<Point> options;
  unsigned long size = playerCells.size();
  Point option(-1, -1);

  // For each of the player's cell, check a path for all 8 directions.
  for (unsigned long c = 0; c < size; c++) {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if ((i != 0) || (j != 0)) {
          option = checkPath(board, player, playerCells.at(c), i, j);

          // Checks if the new cells are in boundaries,
          // because option may include (-1, -1) cells.
          if (board.inBoundaries(option) && !isOptionInList(option, options)) {
            // If the move is valid, and not already in the moves list, add it.
            options.push_back(option);

          }
        }
      }
    }
  }
  return options;
}

Point RegLogic::checkPath(Board &board, const Player &player,
                          const Point &point, int xChange, int yChange) {
  bool passedAtLeastOneRival = false;
  int x = point.getX() + xChange, y = point.getY() + yChange;
  // While the cell being checked is in the board.
  while ((x >= 0) && (x < board.getX()) && (y >= 0) && (y < board.getY())) {
    if (player == *board.getPlayer(x, y)) {
      // If the cell already belongs to the player, return an "empty" cell.
      return Point(-1, -1);
    }
    if (board.getPlayer(x, y) != NULL) {
      // If the cell belongs to the rival continue checking the path in the same direction.
      passedAtLeastOneRival = true;
      x += xChange;
      y += yChange;
    } else if (board.getPlayer(x, y) == NULL) {
      // If the cell is empty and we have passed the rival, return that cell.
      if (passedAtLeastOneRival) {
        return Point(x, y);
      } else {
        // If the cell is empty and have not passed the rival, return an empty cell.
        return Point(-1, -1);
      }
    }
  }
  return Point(-1, -1);
}

void RegLogic::putNewCell(Board &board, Player &player, const Point &newCell) {
  if ((board.getPlayer(newCell.getX(), newCell.getY()) != NULL)
      || (!board.inBoundaries(newCell.getX(), newCell.getY()))) {

    // Cell cannot be put on a non empty cell, or a cell not in the board.
    return;
  }
  vector<Point> toFlip;

  // Put the desired cell.
  board.fillCell(newCell, &player);
  player.increaseScore();

  // Check all 8 direction for cells neede to be flipped.
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if ((i != 0) || (j != 0)) {
        vector<Point> result = checkPathToFlip(board, player, newCell, i, j);
        for (vector<Point>::iterator it = result.begin(); it != result.end();
             ++it) {
          if (!isOptionInList(*it, toFlip)) {
            toFlip.push_back(*it);
          }
        }
      }
    }
  }
  if (!toFlip.empty()) {
    flipCells(board, toFlip, player);
  }
}

vector<Point> RegLogic::checkPathToFlip(const Board &board,
                                        const Player &player,
                                        const Point &point,
                                        int xChange, int yChange) {
  Point toFlip = point;
  vector<Point> cellsToFlip;

  // While the cells in the path are inside the board:
  while (board.inBoundaries(toFlip.getX() + xChange, toFlip.getY() + yChange)) {
    toFlip = Point(toFlip.getX() + xChange, toFlip.getY() + yChange);
    if (board.getPlayer(toFlip.getX(), toFlip.getY()) == NULL) {

      // If there is an empty cell in the middle, no cell should be flipped.
      cellsToFlip.clear();
      return cellsToFlip;
    } else if (*board.getPlayer(toFlip.getX(), toFlip.getY()) != player) {

      // If the cell belongs to the rival add to the list of cells to be flipped.
      cellsToFlip.push_back(toFlip);
    } else if (*board.getPlayer(toFlip.getX(), toFlip.getY()) == player) {

      // End of path, return the cells to be flipped.
      return cellsToFlip;
    }
  }
  cellsToFlip.clear();
  return cellsToFlip;
}

void RegLogic::flipCells(Board &board, vector<Point> cells, Player &player) {
  // Find enemy to update its score.
  Player *enemy;
  for (vector<Point>::iterator it = cells.begin(); it != cells.end(); ++it) {
    if (isEnemy(&player, board.getPlayer(*(it)))) {
      enemy = board.getPlayer(*it);
      break;
    }
  }
  // Fill cell with player and update the scores.
  for (vector<Point>::iterator it = cells.begin(); it != cells.end(); ++it) {
    board.fillCell(*it, &player);
    updateScore(enemy, &player);
  }
}

Point RegLogic::aiMove(Computer &computer, Board &board) {
  vector<Point> moves = getOptionalMoves(board, computer);
  if (moves.empty()) {
    return Point(-1, -1);
  }
  int worstScoreForRival = INT_MAX;
  Point bestPoint = moves.at(0);
  for (vector<Point>::iterator it = moves.begin(); it != moves.end(); ++it) {
    Point option = *it;
    Board test(board);
    int maximumRivalScore = aiFindMaxScore(computer, test, option);
    if (worstScoreForRival > maximumRivalScore) {
      worstScoreForRival = maximumRivalScore;
      bestPoint = option;
    }
  }
  putNewCell(board, computer, bestPoint);
  return bestPoint;
}

int RegLogic::aiFindMaxScore(Computer &comp, Board &board, Point option) {
  Player *rival = findRival(comp, board);
  if (rival == NULL) {
    return 0;
  }

  int compScore = comp.getScore();
  int rivalScore = rival->getScore();
  putNewCell(board, comp, option);

  comp.setScore(compScore);
  rival->setScore(rivalScore);

  int maximumRivalScore = 0;
  vector<Point> rivalOptions = getOptionalMoves(board, *rival);

  for (vector<Point>::iterator it = rivalOptions.begin();
       it != rivalOptions.end(); ++it) {
    int rivalScoreForOneMove = 0;
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if ((i != 0) || (j != 0)) {
          rivalScoreForOneMove +=
              checkPathToFlip(board, *rival, *it, i, j).size();
        }
      }
    }
    if (maximumRivalScore < rivalScoreForOneMove) {
      maximumRivalScore = rivalScoreForOneMove;
    }
  }
  return maximumRivalScore;
}

void RegLogic::updateScore(Player *prevPlayer, Player *currPlayer) {
  if (currPlayer != prevPlayer) {
    currPlayer->increaseScore();
    if (prevPlayer != NULL) {
      prevPlayer->decreaseScore();
    }
  }
}