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

  int activate(string command);

  void getGameList();

  void start(string name);

  void join(string name);
};


#endif //REVERSI_CLIENTCOMMAND_H
