#ifndef EX2NEW_BOARD_H
#define EX2NEW_BOARD_H

#include "cell.h"

class Board {
 private:
  // The width (x) and height (y) of the board.
  int x_, y_;

  // Keep track of how many cells are occupied.
  int counter_;

  // The board is represented as a 2d array of cells.
  Cell **cells_;

 public:
  // Constructor for board. x and y are defaulted to 8.
  explicit Board(int x = 8, int y = 8, Player *players[] = NULL);

  // Copy constructor for board. */
  Board(const Board &board);

  // Destructor for the board. Deleted the 2d array.
  ~Board();

  // Initializes the board with given players at the middle.
  void initialize(Player *const players[]);

  // Returns a specific cell on the board by coordinate.
  Cell *getCell(int i, int j) const;

  // Returns a specific cell on the board by point.
  Cell *getCell(Point point) const;

  // Returns the player of the given coordinate.
  Player *getPlayer(int i, int j) const;

  // Returns the player of the given cell.
  Player *getPlayer(Cell cell) const;

  // Returns the player of the given point.
  Player *getPlayer(Point point) const;

  // Fill cell with player
  void fillCell(Point point, Player *player);

  // Checks if given coordinate is outside of the board's boundaries.
  bool inBoundaries(int x, int y) const;

  // Checks if given point is outside of the board's boundaries.
  bool inBoundaries(Point point) const;

  // Returns the width of the board.
  int getX() const;

  // Returns the height of the board.
  int getY() const;

  // Returns true if the board is full
  bool isFull() const;
};

#endif //EX2NEW_BOARD_H
