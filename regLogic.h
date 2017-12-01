#ifndef REVERSI_REGULARLOGIC_H
#define REVERSI_REGULARLOGIC_H

#include "logic.h"

class RegLogic : public Logic {
 public:
  // Return a cell vector with all possible moves for player p.
  vector<Point> getOptionalMoves(Board &board, const Player &player);

  // Check if a move is possible by reading the cells in a certain direction (path).
  Point checkPath(Board &board, const Player &player, const Point &point,
                  int xChange, int yChange);

  // Change a certain cell to contain the player and flip other cells.
  void putNewCell(Board &board, Player &player, const Point &newCell);

  // For a new cell that was put check which cells of the rival need to be flipped.
  vector<Point> checkPathToFlip(const Board &board, const Player &player,
                                const Point &point, int xChange, int yChange);

  // Flip cells to match player p.
  void flipCells(Board &board, vector<Point> cells, Player &player);

  // Returns movement point for the computer.
  Point aiMove(Computer &computer, Board &board);

  // Finds maximum score of the enemy for the AI to calculate next move.
  int aiFindMaxScore(Computer &comp, Board &board, Point option);

  // Update score for the players. Remove from prevPlayer and add to currPlayer.
  void updateScore(Player *prevPlayer, Player *currPlayer);
};

#endif //REVERSI_REGULARLOGIC_H
