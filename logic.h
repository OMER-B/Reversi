#ifndef REVERSI_LOGIC_H
#define REVERSI_LOGIC_H

#include <vector>
#include "point.h"
#include "player.h"
#include "board.h"
#include "computer.h"

using namespace std;

class Logic {

 public:

  // Virtual destructor for Logic.
  virtual ~Logic();

  // For each cell the belongs to the player, add to the list.
  vector<Point> getPlayerCells(Board &board, const Player &player);

  // Return a cell vector with all possible moves for player p.
  virtual vector<Point> getOptionalMoves(Board &board,
                                         const Player &player) = 0;

  // Check if a move is possible by reading the cells in a certain direction (path).
  virtual Point checkPath(Board &board,
                          const Player &player,
                          const Point &point,
                          int xChange,
                          int yChange) = 0;

  // Change a certain cell to contain the player and flip other cells.
  virtual void putNewCell(Board &board, Player &p, const Point &newCell) = 0;

  // For a new cell that was put check which cells of the rival need to be flipped.
  virtual vector<Point> checkPathToFlip(const Board &board,
                                        const Player &player,
                                        const Point &point,
                                        int xChange,
                                        int yChange) = 0;

  // Flip cells to match player p.
  virtual void flipCells(Board &board, vector<Point> cells, Player &player) = 0;

  // Makes move for the computer.
  virtual Point aiMove(Computer &computer, Board &board) = 0;

  // Finds the maximum score for the enemy.
  virtual int aiFindMaxScore(Computer &computer,
                             Board &otherBoard,
                             Point option) = 0;

  // In order to prevent duplicate moves in the possible moves function
  bool isOptionInList(const Point &newOption, vector<Point> options);

  // Find rival for a player.
  Player *findRival(const Player &currPlayer, const Board &board);

  // Updates the scores of the players.
  virtual void updateScore(Player *prevPlayer, Player *currPlayer) = 0;

  // Returns the winner of the game.
  Player *getWinner(Player *players[]);

  // Returns true if players are enemy of each other.
  bool isEnemy(Player *player1, Player *player2) const;
};

#endif //REVERSI_LOGIC_H
