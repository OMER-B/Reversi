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
  int setUp();

 public:
  // Constructor for the client.
  Client(char *serverIP, int serverPort);

  // Constructor for the client by settings file.
  explicit Client(char *fileName);

  // Destructor for the client.
  ~Client();

  void setDummy_(Dummy *dummy_);

  // Establishes a connection with the server.
  int connectToServer();

  string  getCommand();

  // Makes the move based on players input.
  int makeMove(Board &board, Logic &logic, Display &display);

  // Gets input from the client. Called from makeMove().
  Point getInput(Board &board, Logic &logic, Display &display);

  // Returns the enemy movement that was received so the dummy can make it.
  int getRemoteEnemyMovement();

  // Returns the client's dummy.
  Dummy *getDummy();
};

#endif //REVERSI_CLIENT_H
