//
// Created by h on 27/12/17.
//

#ifndef REVERSI_CLIENTCOMMAND_H
#define REVERSI_CLIENTCOMMAND_H

#include <string>

using namespace std;

class ClientCommand {
 private:
  int clientSocket_;
 public:
  ClientCommand(int clientSocket);

  // Activates a command from the player.
  int activate(string command);

  // Activates the list_games command.
  void getGameList();

  // Activates the start command.
  void start(string name);

  // Activates the join command
  void join(string name);
};

#endif //REVERSI_CLIENTCOMMAND_H
