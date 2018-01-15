#ifndef EX2NEW_GAME_H
#define EX2NEW_GAME_H


#define NUM_OF_PLAYERS 2

#include "board.h"
#include "regLogic.h"
#include "display.h"
#include "consoleDisplay.h"
#include "human.h"

class Game {
 private:

  // The board of the game.
  Board *board_;

  // The logic of the game.
  Logic *logic_;

  // The display type of the game.
  Display *display_;

  // An array of players playing.
  Player *players_[NUM_OF_PLAYERS];

  // Few integers. Can tell from their names.
  int validTurns_;

 public:
  Game(Board *board,
       Logic *logic,
       Display *display,
       Player *first,
       Player *second);

  // Destructor for game. Deleted everything that is allocated.
  ~Game();

  // Plays one turn in the current game.
  void playOneTurn(int current);

  // Starts to play the game until no more valid moves.
  void run();

  // Returns a boolean if the game should stop or continue playing.
  bool shouldStop();

};

#endif //EX2NEW_GAME_H
