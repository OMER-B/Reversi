#ifndef EX2NEW_CONSOLEDISPLAY_H
#define EX2NEW_CONSOLEDISPLAY_H

#include "display.h"

// Display the game in console.
class ConsoleDisplay : public Display {
 public:

  // Destructor for ConsoleDisplay.
  ~ConsoleDisplay();

  // Prints the game board.
  void printBoard(Board *board);
};

#endif //EX2NEW_CONSOLEDISPLAY_H
