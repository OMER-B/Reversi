#include <stdlib.h>
#include "game.h"
#include "client.h"

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
       << "2) Player vs Computer" << endl << "3) Remote player" << endl
       << "Any other selection will exit the game" << endl;
  cin >> gameMode;
  switch (gameMode) {
    case 1:players_[0] = new Human('X');
      players_[1] = new Human('O');
      board_ = new Board(SIZE, SIZE, players_);

      break;
    case 2: players_[0] = new Human('X');
      players_[1] = new Computer('O');
      board_ = new Board(SIZE, SIZE, players_);
      break;
    case 3: {
      char settings[] = "client_config";
      Client *client = new Client(settings);
      Dummy *dummy = new Dummy('D');
      client->setDummy_(dummy);
      try {
        int current = client->connectToServer();
        players_[current] = client;
        players_[1 - current] = dummy;
        board_ = new Board(SIZE, SIZE, players_);
        display_->printBoard(board_);
        if (current == 1) {
          client->getRemoteEnemyMovement();
        }
      } catch (const char *msg) {
        cout << "Failed to connect to server. Reason: " << msg << endl;
        exit(-1);
      }
      break;
    }
    default:cout << "Bye";
      exit(0);
  }
  logic_ = new RegLogic();
}

void Game::run() {
  setGameMode();  // Choose if player is human or computer.
  numberOfPlayers_ = (sizeof(players_) / sizeof(players_[0]));

  // Game loop to play one turn until shouldStop() turns false.
  while (!shouldStop()) {
    playOneTurn();
  }

  cout << "The final score is: " << endl;
  for (int i = 0; i < numberOfPlayers_; i++) {
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

void Game::playOneTurn() {
  int temp = validTurns_;
  int moreTurns =
      players_[currentPlayer_]->makeMove(*board_, *logic_, *display_);
  validTurns_ += moreTurns;
  if (validTurns_ == temp) {
    validTurns_ = 0;
  }
  currentPlayer_ = (currentPlayer_ + 1) % playersSize_;
}

bool Game::shouldStop() {
  return board_->isFull() || (validTurns_ >= numberOfPlayers_);
}