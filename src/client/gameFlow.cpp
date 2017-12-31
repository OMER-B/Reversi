
#include "gameFlow.h"

Game::Game(Board *board_,
           Logic *logic_,
           Display *display_,
           Player *first,
           Player *second) : board_(board_),
                             logic_(logic_),
                             display_(display_) {
  players_[0] = first;
  players_[1] = second;
  validTurns_ = 0;
}

Game::~Game() {
  delete board_;
  delete display_;
  delete logic_;
  delete players_[0];
  delete players_[1];
}

void Game::run() {
  display_->printBoard(board_);
  int current = 0;
  // Game loop to play one turn until shouldStop() turns false.
  while (!shouldStop()) {
    playOneTurn(current);
    current = 1 - current;
  }

  cout << "The final score is: " << endl;
  for (int i = 0; i < NUM_OF_PLAYERS; i++) {
    cout << players_[i]->getSymbol() << " with "
         << players_[i]->getScore() << " points." << endl;
  }
  cout << endl;
  if (logic_->isTie(*players_[0], *players_[1])) {
    cout << "It's a tie!" << endl;
  } else {
    Player *winner = logic_->getWinner(players_);
    cout << "Winner is: '" << *winner << "' with score of "
         << winner->getScore()
         << endl;
  }
}

void Game::playOneTurn(int current) {
  cout << "current player: " << players_[current]->getSymbol() << endl;

  int numOfNoMoves =
      players_[current]->makeMove(*board_, *logic_, *display_);
  if (numOfNoMoves == 0) {
    validTurns_ = 0;
    return;
  }
  validTurns_ += numOfNoMoves;

}

bool Game::shouldStop() {
  return board_->isFull() || (validTurns_ >= NUM_OF_PLAYERS);
}
