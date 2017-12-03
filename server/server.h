#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include "../point.h"

class Server {
 private:
  int port_;
  int serverSocket_;
  void handleClients(int firstClient, int secondClient);

 public:
  Server(int port);
  Server(char *file);
  void start();
  void stop();
};

#endif //REVERSI_SERVER_H
