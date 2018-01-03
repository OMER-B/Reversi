#ifndef REVERSI_COMMANDJOIN_H
#define REVERSI_COMMANDJOIN_H

#include "command.h"
#include "HandleGame.h"
#include "Lobby.h"

#include <iostream>
#include <vector>
using namespace std;

typedef struct runArgs {
  Room room;
  HandleGame *handleGame;
} runArgs;

class CommandJoin : public Command {

 private:
  Lobby *lobby_;
  HandleGame *handleGame_;
  vector<pthread_t *> *threads_;

 public:
  // Constructor for join command.
  CommandJoin(Lobby *, HandleGame *, vector<pthread_t *> *);

  // Command to join an existing game.
  bool execute(string arg, int clientSocket);
};

#endif //REVERSI_COMMANDJOIN_H