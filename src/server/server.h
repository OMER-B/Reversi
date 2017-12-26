#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include <string>
#include <vector>
#include "Lobby.h"
#include "command.h"
#include "commandsManager.h"
#include "HandleGame.h"


typedef struct FirstThreadArgs{

}FirstThreadArgs;

typedef struct SecondThreadArgs{
  CommandsManager *manager;
  int clientSocket;
  pthread_t id;
}SecondThreadArgs;

using namespace std;

class Server {
 private:
  Lobby * lobby_;
  vector<pthread_t *> *threads_;
  CommandsManager *manager_;
  HandleGame * handleGame_;
  int serverSocket_; // Socket of the server.
  int port_; // Port for the server.

 public:
  // Constructor by port.
  explicit Server(int port__);

  // Constructor by file with port details.
  explicit Server(char *fileName);


  // Destructor for the server.
  ~Server();

  // Start the server and accept new clients.
  void start();

  // close the server's socket.
  void stop();

};


// in a new thread
//send the class of game and class of Lobby
static void* handleClient(void * args);

static pair<string, vector<string> > seperate(string input);

#endif //REVERSI_SERVER_H