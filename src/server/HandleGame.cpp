#include <unistd.h>
#include "HandleGame.h"
#include "commandsManager.h"
#include <cstring>
#include "server.h"
using namespace std;

void notify(int clients[]) {
  char NUM0[2] = "0";
  char NUM1[2] = "1";

  cout << "Notifying clients who is who." << endl;

  ssize_t n = write(clients[0], &NUM0, sizeof(NUM0));
  if (n == -1) {
    cout << "Error writing to socket" << endl;
    return;
  }
  n = write(clients[1], &NUM1, sizeof(NUM1));
  if (n == -1) {
    cout << "Error writing to socket" << endl;
    return;
  }
}
void *HandleGame::play(void *room) {
  Room *game = (Room *) room;
  //read the move of the first player, and send to the second
  CommandsManager *cm = CommandsManager::getInstance();
  int clients[2];
  clients[0] = game->getFirstClient();
  clients[1] = game->getSecondClient();

  notify(clients);

  int i = 0;
  char move[BUFFER];
  char go[] = "go";
  ssize_t n;
  char error[] = "close";
  while (true) {
    memset(move, 0, sizeof(move));
    // Read new point from client.
    n = write(clients[i], &go, sizeof(go));
    if (n == -1) {
      cout << "Error reading from client " << clients[i % 2] << endl;
      n = write(clients[1 - i], &error, sizeof(error));
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }
    cout << "sent feedback to: " << clients[i] << endl;
    n = read(clients[i], &move, sizeof(move));
    if (n == -1) {
      cout << "Error reading from client " << clients[i % 2] << endl;
      n = write(clients[1 - i], &error, sizeof(error));
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }
    cout << "got move from client" << i << ": " << move << endl;

    n = write(clients[(1 - i)], &move, sizeof(move));
    cout << "sent to client " << (1 - i) << ": " << move << endl;

    i = 1 - i;
    if (n == -1) {
      cout << "Error reading from client " << clients[i % 2] << endl;
      n = write(clients[1 - i], &error, sizeof(error));
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }
    if (n == 0) {
      cout << "Client disconnected" << endl;
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }

    if (strcmp(move, "close") == 0) {
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }
  }
}