#ifndef REVERSI_COMMANDJOIN_H
#define REVERSI_COMMANDJOIN_H

#include "command.h"
#include "HandleGame.h"
#include "Lobby.h"

#include <iostream>
#include <vector>
using namespace std;

typedef struct runArgs{
  Room room;
  HandleGame *handleGame;
} runArgs;

class CommandJoin : public Command {

private:
  Lobby *lobby_;
  HandleGame * handleGame_;

public:
  CommandJoin(Lobby *lobby, HandleGame * handleGame);
  void execute(vector<string> &args, int clientSocket);
  //static void *run(void *runArgs);
};

#endif //REVERSI_COMMANDJOIN_H