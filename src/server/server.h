#ifndef REVERSI_SERVER_H
#define REVERSI_SERVER_H

#include <string>
#include <vector>

using namespace std;

typedef enum Status { Waiting, Active, Ended };

typedef struct Room {
  string name;
  int firstClient;
  int secondClient;
  int threadID;
  Status status;
} Room;

//server, currClientSocket and threadNumber (who to close)

class Server {
 private:
  map<string, Room *> *lobby; // Needs to be a pointer and member of server.

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

  pair<string, vector<string>> seperate(string input);
};

#endif //REVERSI_SERVER_H
