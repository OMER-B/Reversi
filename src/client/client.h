#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H
#include <string>
#include "point.h"
#include "board.h"
#include "human.h"
#include "dummy.h"

class Client : public Human {
 private:
  // Dummy holds the next enemy's movement.
  Dummy *dummy_;

  // The IP of the server.
  string serverIP_;

  // The port of the server.
  int serverPort_;

  // The client's socket.
  int clientSocket_;

  // Sets up the clients symbol and dummy.
  void setUp(int index);

 public:
  int getClientSocket_() const;

  // Constructor for the client.
  Client(char *serverIP, int serverPort);

  // Constructor for the client by settings file.
  explicit Client(char *fileName);

  // Destructor for the client.
  ~Client();

  void setDummy_(Dummy *dummy_);

  // Establishes a connection with the server.
  void connectToServer();

  // Returns the index of the player.
  int indexOfPlayer();

  string getCommand();

  // Makes the move based on players input.
  int makeMove(Board &board, Logic &logic, Display &display);

  // Returns the client's dummy.
  Dummy *getDummy();
};

#endif //REVERSI_CLIENT_H
