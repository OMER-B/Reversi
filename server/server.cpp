#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;
#define MAX_CLIENTS 2

Server::Server(int port) : port_(port) {}

Server::Server(char *fileName) {
  ifstream file(fileName, ios::in);
  string buffer, ip;
  getline(file, buffer);
  getline(file, buffer);
  port_ = atoi(buffer.c_str());
}

void Server::stop() {
  close(serverSocket_);
}

void Server::start() {
  int firstClientSocket, secondClientSocket;

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

    // First client.
    firstClientSocket = accept(serverSocket_, (struct sockaddr *) &clientAddress, &clientAddressLen);
    cout << "First client connected." << endl;

    // Second client.
    secondClientSocket = accept(serverSocket_, (struct sockaddr *) &clientAddress, &clientAddressLen);
    cout << "Second client connected." << endl;

    handleClients(firstClientSocket, secondClientSocket);
    break;
  }

  // Close communication with the client.
  close(firstClientSocket);
  close(secondClientSocket);
}

void Server::handleClients(int firstClient, int secondClient) {
  char move[6];
  while (true) {
    // First player turn.
    memset(move, 0, sizeof(move));
    ssize_t n = read(firstClient, move, sizeof(move));
    cout << "Got move: " << *move << endl;
    n = write(firstClient, move, sizeof(move));
    if (strcmp(move, "End") == 0) {
      break;
    }

    // Second player turn.
    memset(move, 0, sizeof(move));
    n = read(secondClient, move, sizeof(move));
    cout << "Got move: " << *move << endl;
    n = write(secondClient, move, sizeof(move));
    if (strcmp(move, "End") == 0) {
      break;
    }
  }
}