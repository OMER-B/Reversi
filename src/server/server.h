#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include <sys/socket.h>
#include <pthread.h>
#include <string>
#include <vector>
#include <netinet/in.h>
#include "Lobby.h"
#include "command.h"
#include "commandsManager.h"
#include "HandleGame.h"

#define BUFFER 256
#define MAX_CONNECTED_CLIENTS 10

typedef struct firstThreadArgs {
  int serverSocket;
  CommandsManager *manager;
  vector<pthread_t *> *threads;
} FirstThreadArgs;

typedef struct secondThreadArgs {
  CommandsManager *manager;
  int clientSocket;
  pthread_t id;
} SecondThreadArgs;

using namespace std;

class Server {
 private:
  Lobby *lobby_;
  vector<pthread_t *> *threads_; // li
  CommandsManager *manager_;
  HandleGame *handleGame_;
  int serverSocket_; // Socket of the server.
  int port_; // Port for the server.
  bool stop_;

 public:
  // Handles the clients as a threaded function.
  static void *handleClient(void *args);

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

  // Checks if the server should close (by "exit").
  static void *shouldStop(void *server);
};

#endif //REVERSI_SERVER_H