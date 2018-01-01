#include "gameFlow.h"
#include "client.h"

int main() {

  Board *board;
  Logic *logic;
  Display *display;
  Player *players[2];

  int gameMode;
  cout << "Choose a game mode: " << endl << "1) Player vs Player" << endl
       << "2) Player vs Computer" << endl << "3) Remote player" << endl
       << "Any other selection will exit the game" << endl;
  cin >> gameMode;
  cin.ignore();
  switch (gameMode) {
    case 1:players[0] = new Human('X');
      players[1] = new Human('O');
      break;
    case 2:players[0] = new Human('X');
      players[1] = new Computer('O');
      break;
    case 3: {
      char settings[] =
          "/home/h/CLionProjects/Reversi/src/client/client_config";
      Client *client = new Client(settings);
      Dummy *dummy = new Dummy('D');
      client->setDummy_(dummy);
      int current;
      try {
        client->connectToServer();
        dummy->setClientSocket(client->getClientSocket_());

      } catch (const char *msg) {
        cout << "Failed to connect to server. Reason: " << msg << endl;
        exit(-1);
      }
      cout << "connected to server" << endl;
      current = client->indexOfPlayer();
      if (current == -1) {
        cout << "You did not start a game. see you next time." << endl;
        exit(0);
      }
      players[current] = client;
      players[1 - current] = dummy;
      break;
    }
    default:cout << "Bye";
      exit(0);
  }
  display = new ConsoleDisplay;
  board = new Board(SIZE, SIZE, players);
  logic = new RegLogic();

  Game game(board, logic, display, players[0], players[1]);
  game.run();
  return 0;
}
