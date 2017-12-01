#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include "point.h"

class Server {
 private:
  int port_;
  int serverSocket_;
  void handleClient(int firstClient, int secondClient);

 public:
  Server(int port);
  void start();
  void stop();
};

#endif //REVERSI_SERVER_H
