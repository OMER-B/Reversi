#include <iostream>
#include "game.h"
#include "server/server.h"

using namespace std;

int main() {
  Game *game = new Game();
  game->run();
  delete game;
  return 0;
}