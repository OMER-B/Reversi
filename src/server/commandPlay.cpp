
#include <unistd.h>
#include <cstring>
#include "commandPlay.h"
#define BUFFER 15

void CommandPlay::execute(string arg, int clientSocket) {
  char move[BUFFER];
  memset(move, 0, sizeof(move));
  strcpy(move, arg.c_str());
  ssize_t n = write(clientSocket, &move, sizeof(move));
}