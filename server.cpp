#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

using namespace std;
#define MAX_CLIENTS 2

void Server::handleClient(int firstClient, int secondClient) {
  char move[6];

  while (true) {
    int n = read(firstClient, move, sizeof(move));
    if (n == -1) {
      cout << "Error reading move." << endl;
      return;
    }
    if (n == 0) {
      cout << "Client disconnected." << endl;
      return;
    }

    cout << "Got move: " << *move << endl;

    int result;
    n = write(firstClient, &result, sizeof(result));
    if (n == -1) {
      cout << "Error writing to socket." << endl;
      return;
    }
  }
}

Server::Server(int port) : port_(port) {

}

void Server::start() {
  // Create a socket point.
  serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket_ == -1) {
    throw "Error opening socket.";
  }

  // Assign a local address to the socket.
  struct sockaddr_in serverAddress;
  bzero((void *) &serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port_);
  if (bind(serverSocket_, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
    throw "Error on binding.";
  }
  // Start listening to incoming connections.
  listen(serverSocket_, MAX_CLIENTS);

  // Define the client socket's structures.
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLen;

  while (true) {
    cout << " Waiting for clients." << endl;

    // Accept new client connection.
    int firstClientSocket = accept(serverSocket_, (struct sockaddr *) &clientAddress, &clientAddressLen);
    cout << "First client connected." << endl;
    if (firstClientSocket == -1) {
      throw "Error on accept.";
    }

    int secondClientSocket = accept(serverSocket_, (struct sockaddr *) &clientAddress, &clientAddressLen);
    cout << "Second client connected." << endl;
    if (secondClientSocket == -1) {
      throw "Error on accept.";
    }
    handleClient(firstClientSocket, secondClientSocket);

    // Close communication with the client.
    close(firstClientSocket);
    close(secondClientSocket);
  }

}

void Server::stop() {
  close(serverSocket_);

}