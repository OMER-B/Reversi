
#include <unistd.h>
#include <cstring>
#include "commandPlay.h"
#define BUFFER 15

void CommandPlay::execute(vector<string> &args, int clientSocket) {
  char move[BUFFER];
  memset(move, 0, sizeof(move));
  strcpy(move, args[0].c_str());
  ssize_t n = write(clientSocket, &move, sizeof(move));
}