#include <unistd.h>
#include "HandleGame.h"
#include "commandsManager.h"
#include <cstring>
#include "server.h"
using namespace std;
#define BUFFER 128

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

  int clients[2];
  clients[0] = game->getFirstClient();
  clients[1] = game->getSecondClient();

  notify(clients);

  int i = 0;
  char move[BUFFER];
  CommandsManager *manager = CommandsManager::getInstance();
  while (true) {
    // Read new point from client.
    ssize_t n = read(clients[(i % 2)], &move, sizeof(move));
    if (n == -1) {
      cout << "Error reading from client " << clients[i % 2] << endl;
      break;
    }
    if (n == 0) {
      cout << "Client disconnected" << endl;
      break;
    }

    /* CHANGE INPUT TO COMMAND */
    string command = manager->seperate(move).first;
    vector<string> stringArgs = manager->seperate(move).second;

    if (manager->isLegalCommand(command, clients[(i % 2)])) {
      if (strcmp(command.c_str(), "play") == 0 || strcmp(command.c_str(), "close") == 0) {
        manager->executeCommand(command, stringArgs, clients[(i + 1) % 2]);
      }
    } else {
      // print "invalid command"
    }
    i++;
  }
}