#ifndef REVERSI_COMMANDSTART_H
#define REVERSI_COMMANDSTART_H

#include "command.h"
#include "Lobby.h"
#include <vector>

using namespace std;

class CommandStart : public Command {
  Lobby *lobby_;
 public:
  // Constructor for the start command.
  explicit CommandStart(Lobby *lobby);

  // Execute the start command to start a new room.
  bool execute(string arg, int clientSocket);
};

#endif //REVERSI_COMMANDSTART_H