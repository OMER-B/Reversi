#include "server.h"
#include "commands/commandsManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <arpa/inet.h>
#include <sstream>

#define BUFFER 256

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
  bzero((void *) &serverAddress, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(port_);
  if (bind(serverSocket_, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1) {
    throw "Error on binding";
  }
  cout << "Binding succeeded." << endl;
  // Start listening to incoming connections
  listen(serverSocket_, MAX_CONNECTED_CLIENTS);
  // Define the client socket's structures
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLen;
  //thread main process with (if == exit) ((FOR SERVER)))

  while (true) {
    // Accept a new clients connections.
    int clientSocket = accept(serverSocket_, (struct sockaddr *) &clientAddress, &clientAddressLen);
    cout << "First client connected" << endl;
    if (clientSocket == -1) {
      throw "Error on first client accept";
    }
    //pthread_create()    //send handle clients and the three parameters.

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*handleClient)(void *), void *args);
  }
}

static void Server::handleClient(Lobby *lobby, HandleGame *handleGame ,int clientSocket) {
  char input[BUFFER];
  memset(input, 0, sizeof(input));

  CommandsManager manager(Lobby *lobby, HandleGame *handleGame);
  ssize_t n = read(clientSocket, &input, sizeof(input));

  string command;
  vector<string> args;
  command = seperate(input).first;
  args = seperate(input).second;
  //manager.excecuteCommand(command, args, clientSocket);
}



static std::pair<string, vector<string>> Server::seperate(string input) {
  stringstream stream(input);
  string command;
  string buffer;
  vector<string> args;

  stream >> command;
  while (stream >> buffer) {
    args.push_back(buffer);
  }
  return pair<string, vector<string>>(command, args);
}


Server::~Server() {
  stop();
}

void Server::stop() {
  close(serverSocket_);
}

