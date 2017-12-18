#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <arpa/inet.h>

#define BUFFER 10

using namespace std;
#define MAX_CONNECTED_CLIENTS 2
Server::Server(int port) : serverSocket_(0) {
  port_ = port;
  cout << "Server" << endl;
}

Server::Server(char *fileName) {
  ifstream inFile;
  inFile.open(fileName);
  inFile >> port_;
  inFile.close();
  cout << "Server port: " << port_ << endl;
}

void Server::start() {
  // Create a socket point
  serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket_ == -1) {
    throw "Error opening socket";
  }
  // Assign a local address to the socket
  struct sockaddr_in serverAddress;
  bzero((void *) &serverAddress,
        sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port_);
  if (bind(serverSocket_,
           (struct sockaddr *) &serverAddress,
           sizeof(serverAddress)) == -1) {
    throw "Error on binding";
  }
  cout << "Binding succeeded." << endl;
  // Start listening to incoming connections
  listen(serverSocket_, MAX_CONNECTED_CLIENTS);
  // Define the client socket's structures
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLen;

  while (true) {
    cout << "Waiting for connections..." << endl;

    // Accept a new clients connections.
    int firstClientSocket = accept(serverSocket_,
                                   (struct sockaddr *) &clientAddress,
                                   &clientAddressLen);
    cout << "First client connected" << endl;
    if (firstClientSocket == -1) {
      throw "Error on first client accept";
    }
    int secondClientSocket = accept(serverSocket_,
                                    (struct sockaddr *) &clientAddress,
                                    &clientAddressLen);
    cout << "Second client connected" << endl;
    if (secondClientSocket == -1) {
      throw "Error on second client accept";
    }

    cout << "Game has started" << endl;
    handleClient(firstClientSocket, secondClientSocket);

    // Close communication with the clients.
//    close(firstClientSocket);
//    close(secondClientSocket);
  }
}

void Server::notifyClients(int clients[]) {
  int NUM0 = 0;
  int NUM1 = 1;

  cout << "Notifying clients who is who." << endl;

  ssize_t n = write(clients[0], &NUM0, sizeof(NUM0));
  if (n == -1) {
    cout << "Error writing to socket" << endl;
    return;
  }
  n = write(clients[1], &NUM1, sizeof(NUM1));
  if (n == -1) {
    cout << "Error writing to socket" << endl;
    return;
  }
}

void Server::handleClient(int firstClient, int secondClient) {
  int i = 0;
  char move[BUFFER];
  ssize_t n;
  int clients[] = {firstClient, secondClient};

  notifyClients(clients);

  while (true) {
    // Read new point from client.
    n = read(clients[(i % 2)], &move, sizeof(move));
    if (n == -1) {
      cout << "Error reading row" << endl;
      break;
    }
    if (n == 0) {
      cout << "Client disconnected" << endl;
      break;
    }
    if (strcmp(move, "0 0") == 0) {
      n = write(clients[(i + 1) % 2], &move, sizeof(move));
      if (n == -1) {
        cout << "Error writing to socket" << endl;
        break;
      }
      cout << "Game has ended by exit from " << clients[(i % 2)] << endl;
      break;
    }
    if (strcmp(move, "-1 -1") != 0) {
      cout << "Got move (" << move << ") from " << clients[(i % 2)] << endl;
    }
    // Write the point back to the other client.
    n = write(clients[(i + 1) % 2], &move, sizeof(move));
    if (n == -1) {
      cout << "Error writing to socket" << endl;
      break;
    }
    i++;
  }
}

Server::~Server() {
  stop();
}

void Server::stop() {
  close(serverSocket_);
}

