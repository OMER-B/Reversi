#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include <string>

using namespace std;

class Server {
 private:
  // Socket of the server.
  int serverSocket_;

  // Port for the server.
  int port_;

  // Gets info from the players and transfer it between them.
  void handleClient(int firstClient, int secondCleint);

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

  // Notify the clients who they are.
  void notifyClients(int clients[]);
};

#endif //REVERSI_SERVER_H
