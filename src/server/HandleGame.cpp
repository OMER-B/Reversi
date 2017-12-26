#include <unistd.h>
#include "HandleGame.h"
#include <iostream>
#include <cstring>

using namespace std;
#define BUFFER 128

static void * HandleGame::play(void *room) {
  Room *game = (Room*)room;
  //read the move of the first player, and send to the second

  int clients[2];
  clients[0] = game->getFirstClient();
  clients[1] = game->getSecondClient();

  int NUM0 = 0;
  int NUM1 = 1;

  cout << "Notifying clients who is who." << endl;

  ssize_t n = write(clients[0], &NUM0, sizeof(NUM0));
  if (n == -1) {
    cout << "Error writing to socket" << endl;
    return NULL;
  }
  n = write(clients[1], &NUM1, sizeof(NUM1));
  if (n == -1) {
    cout << "Error writing to socket" << endl;
    return NULL;
  }

  int i = 0;
  char move[BUFFER];

  while (true) {
    // Read new point from client.
    ssize_t n = read(clients[(i % 2)], &move, sizeof(move));
    if (n == -1) {
      cout << "Error reading row" << endl;
      break;
    }
    if (n == 0) {
      cout << "Client disconnected" << endl;
      break;
    }
    if (strcmp(move, "0 0") == 0) {
      n = write(clients[(i + 1) % 2], &move, sizeof(move));
      if (n == -1) {
        cout << "Error writing to socket" << endl;
        break;
      }
      cout << "Game has ended by exit from " << clients[(i % 2)] << endl;
      break;
    }
    if (strcmp(move, "-1 -1") != 0) {
      cout << "Got move (" << move << ") from " << clients[(i % 2)] << endl;
    }
    // Write the point back to the other client.
    n = write(clients[(i + 1) % 2], &move, sizeof(move));
    if (n == -1) {
      cout << "Error writing to socket" << endl;
      break;
    }
    i++;
  }
}