#ifndef EX2NEW_GAME_H
#define EX2NEW_GAME_H

#define SIZE 8

#include "board.h"
#include "regLogic.h"
#include "display.h"
#include "consoleDisplay.h"
#include "human.h"

class Game {
 private:
  // Currently set for a game of two players.
  static const int playersSize_ = 2;

  // The board of the game.
  Board *board_;

  // The logic of the game.
  Logic *logic_;

  // The display type of the game.
  Display *display_;

  // An array of players playing.
  Player *players_[playersSize_];

  // Few integers. Can tell from their names.
  int numberOfPlayers_, validTurns_, currentPlayer_;

 public:
  // Constructor for game.
  Game();

  // Destructor for game. Deleted everything that is allocated.
  ~Game();

  // Plays one turn in the current game.
  void playOneTurn();

  // Starts to play the game until no more valid moves.
  void run();

  // Returns a boolean if the game should stop or continue playing.
  bool shouldStop();

  // Sets the game mode as player vs player, player vs computer, etc...
  void setGameMode();
};

#endif //EX2NEW_GAME_H
