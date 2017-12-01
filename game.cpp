#include <limits>
#include "game.h"
#include "computer.h"
#include <cstdlib>

Game::Game() : players_(), numberOfPlayers_(), validTurns_(), currentPlayer_() {
  display_ = new ConsoleDisplay();
}

Game::~Game() {
  delete board_;
  delete display_;
  delete logic_;
  delete players_[0];
  delete players_[1];
}

void Game::setGameMode() {
  int gameMode;
  cout << "Choose a game mode: " << endl << "1) Player vs Player" << endl
       << "2) Player vs Computer" << endl << "3) Computer vs Computer" << endl
       << "Any other selection will exit the game" << endl;
  cin >> gameMode;
  switch (gameMode) {
    case 1:players_[0] = new Human('X');
      players_[1] = new Human('O');
      break;
    case 2: players_[0] = new Human('X');
      players_[1] = new Computer('O');
      break;
    case 3: players_[0] = new Computer('X');
      players_[1] = new Computer('O');
      break;
    default:cout << "Bye";
      exit(0);
  }
  board_ = new Board(SIZE, SIZE, players_);
  logic_ = new RegLogic();
}

void Game::run() {
  setGameMode();  // Choose if player is human or computer.
  cout << "First player will be BLACK. " << endl
       << "Enter coordinates in the following format: 'row col'" << endl;

  numberOfPlayers_ = (sizeof(players_) / sizeof(players_[0]));

  // Game loop to play one turn until shouldStop() turns false.
  while (!shouldStop()) {
    playOneTurn();
  }

  Player *winner = logic_->getWinner(players_);
  cout << "Winner is: '" << *winner << "' with score of " << winner->getScore()
       << endl;
}

void Game::playOneTurn() {
  while (!shouldStop()) {
    cout << "CURRENT BOARD:\t\t\t\t\t\t\t";
    for (int i = 0; i < numberOfPlayers_; i++) {
      cout << players_[i]->getSymbol() << ":"
           << players_[i]->getScore() << "\t\t";
    }
    cout << endl;
    display_->printBoard(board_);
    int temp = validTurns_;
    validTurns_ += players_[currentPlayer_]->makeMove(*board_, *logic_);
    if (validTurns_ == temp) {
      validTurns_ = 0;
    }
    currentPlayer_ = (currentPlayer_ + 1) % playersSize_;

  } // End of while.

  cout << "No more moves to play." << endl;
  cout << "FINAL BOARD:\t\t\t\t\t\t\t";
  for (int i = 0; i < numberOfPlayers_; i++) {
    cout << players_[i]->getSymbol() << ":"
         << players_[i]->getScore() << "\t\t";
  }

  // Prints the final board.
  cout << endl;
  display_->printBoard(board_);
}

bool Game::shouldStop() {
  return board_->isFull() || (validTurns_ == numberOfPlayers_);
}



