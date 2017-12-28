//
// Created by omer on 28/12/17.
//

#ifndef REVERSI_COMMANDPLAY_H
#define REVERSI_COMMANDPLAY_H

#include "command.h"
class CommandPlay : public Command {
  void execute(string arg, int clientSocket);

};

#endif //REVERSI_COMMANDPLAY_H
