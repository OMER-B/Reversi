#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include <string>
#include <vector>
#include "commands/command.h"
#include "commands/commandsManager.h"
#include "HandleGame.h"

using namespace std;
class Lobby; 
//server, currClientSocket and threadNumber (who to close)

class Server {
 private:

  // Socket of the server.
  int serverSocket_;

  // Port for the server.
  int port_;

 public:
  // Constructor by port.
  explicit Server(int port__);

  // Constructor by file with port details.
  explicit Server(char *fileName);

  // in a new thread
  //send the class of game and class of lobby
  static void handleClient(Lobby *lobby, HandleGame *handleGame ,int clientSocket);

  // Destructor for the server.
  ~Server();

  // Start the server and accept new clients.
  void start();

  // close the server's socket.
  void stop();

  static pair<string, vector<string>> seperate(string input);
};

#endif //REVERSI_SERVER_H
