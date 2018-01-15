#include <unistd.h>
#include "HandleGame.h"
#include "commandsManager.h"
#include <cstring>
#include "server.h"
#include "../tools.h"

using namespace std;

void notify(int clients[]) {
  char NUM0[BUFFER];
  char NUM1[BUFFER];

  strcpy(NUM0, "0");
  strcpy(NUM1, "1");
  
  cout << "Notifying clients who is who. First is " << clients[0] << endl;

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
  char go[BUFFER];
  char error[BUFFER];
  memset(go, 0, sizeof(move));
  memset(error, 0, sizeof(move));
  strcpy(go, "go");
  strcpy(error, "close");
  ssize_t n;
  while (true) {
    memset(move, 0, sizeof(move));
    // Read new point from client.
    n = write(clients[i], &go, sizeof(go));
    cout << "Sent " << clients[i] << ": " << go << endl;
    if (n == -1) {
      cout << "Error reading from client " << clients[i % 2] << endl;
      n = write(clients[1 - i], &error, sizeof(error));
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }
    n = read(clients[i], &move, sizeof(move));
    cout << "recieved: " << move << " from: " << clients[i] << endl;
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

    if (strcmp(move, "close") == 0) {
      cm->executeCommand("close", game->getName(), clients[i]);
      break;
    }
  }
}