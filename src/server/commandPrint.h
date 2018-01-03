#ifndef REVERSI_COMMANDPRINT_H
#define REVERSI_COMMANDPRINT_H

#include "command.h"
#include "Lobby.h"
#include <vector>
#include <iostream>
using namespace std;

class CommandPrint : public Command {
 private:
  Lobby *lobby_;

 public:
  // Constructor for print command.
  CommandPrint(Lobby *lobby);

  // Command to print all existing available games.
  bool execute(string arg, int clientSocket);
};

#endif //REVERSI_COMMANDPRINT_H