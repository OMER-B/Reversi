#ifndef EX2NEW_CELL_H
#define EX2NEW_CELL_H

#include <iostream>
#include <ostream>
#include "player.h"
#include "point.h"

class Cell {
 private:
  // x, y are coordinates for the cell.
  Point point_;

  // The player who occupies the cell.
  Player *player_;

 public:
  // Constructor for cell receives x, y coordinates.
  explicit Cell(int x = 0, int y = 0);

  // Constructor by point.
  explicit Cell(Point p);

  // Destructor for cell.
  ~Cell();

  // Returns a string representation of the cell (AKA symbol of the player).
  char getSymbol() const;

  // Returns x coordinate of the cell.
  int getX() const;

  // Returns y coordinate of the cell.
  int getY() const;

  // Sets x coordinate for the cell.
  void setX(int x_);

  // Sets y coordinate for the cell.
  void setY(int y_);

  // Returns the player who occupies the cell.
  Player *getPlayer();

  // A boolean to check if the cell is empty or not.
  bool isEmpty();

  // Fills the cell with given player.
  void fill(Player *p);

  // Compares two cells.
  bool operator==(const Cell &otherCell) const;

  // Compares two cells.
  bool operator!=(const Cell &otherCell) const;
};

// Prints the cell as (x, y).
std::ostream &operator<<(std::ostream &out, Cell const &c);

#endif //EX2NEW_CELL_H
