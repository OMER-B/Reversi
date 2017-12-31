#include "server.h"
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <arpa/inet.h>

using namespace std;

Server::Server(int port) : serverSocket_(0) {
  port_ = port;
  lobby_ = new Lobby;
  threads_ = new vector<pthread_t *>;
  handleGame_ = new HandleGame;
  manager_ = CommandsManager::getInstance(lobby_, handleGame_);
  stop_ = false;
}

Server::Server(char *fileName) {
  threads_ = new vector<pthread_t *>;
  lobby_ = new Lobby;
  handleGame_ = new HandleGame;
  manager_ = CommandsManager::getInstance(lobby_, handleGame_);
  stop_ = false;
  ifstream inFile;
  inFile.open(fileName);
  inFile >> port_;
  inFile.close();
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
  cout << "Binding succeeded. Server is up." << endl;
  // Start listening to incoming connections
//  listen(serverSocket_, MAX_CONNECTED_CLIENTS);
//  // Define the client socket's structures
//  struct sockaddr_in clientAddress[MAX_CONNECTED_CLIENTS];
//  socklen_t clientAddressLen[MAX_CONNECTED_CLIENTS];


  pthread_t serv;
  pthread_create(&serv, NULL, shouldStop, (void *) this);

  listen(serverSocket_, MAX_CONNECTED_CLIENTS);
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLen;

  while (!stop_) {
    // Accept a new clients connections.
    int clientSocket = accept(serverSocket_,
                              (struct sockaddr *) &clientAddress,
                              &clientAddressLen);
    cout << "Client connected" << endl;
    if (clientSocket == -1) {
      throw "Error on first client accept";
    }
    SecondThreadArgs args;
    args.clientSocket = clientSocket;
    args.manager = manager_;
    pthread_t id;
    threads_->push_back(&id);
    pthread_create(&id, NULL, handleClient, &args);
  }
}

void *Server::handleClient(void *args) {
  SecondThreadArgs *clientArgs = (SecondThreadArgs *) args;
  CommandsManager *manager = clientArgs->manager;

  bool shoulContinue = true;

  while(shoulContinue) {
    char input[BUFFER];
    memset(input, 0, sizeof(input));

    cout << "connected to client: " << clientArgs->clientSocket << endl;
    ssize_t n = read(clientArgs->clientSocket, &input, sizeof(input));
    if (n == -1) {
      throw "Failed to receive read from client";
    }

    string stringArgs;

    pair<string, string> result;
    result = manager->seperate(input);

    string command = result.first;
    stringArgs = result.second;
    if (manager->isLegalCommand(command, clientArgs->clientSocket)) {
      shoulContinue = manager->executeCommand(command, stringArgs, clientArgs->clientSocket);
    } else {
      cout << "Illegal command" << endl;
    }

  }
}

Server::~Server() {
  close(serverSocket_);
  stop();
  delete threads_;
  delete lobby_;
  delete manager_;
  delete handleGame_;
}

void Server::stop() {
  cout << "Closing the server..." << endl;
  stop_ = true;
  map<string, Room *> *mappa = lobby_->getMap();
  for (vector<pthread_t *>::iterator it = threads_->begin();
       it != threads_->end(); ++it) {
    pthread_cancel(**it);

  }

  char input[] = "close";
  for (map<string, Room *>::iterator it = mappa->begin(); it != mappa->end();
       ++it) {
    cout << "Closing room '" << (*it).second->getName() << "'" << endl;
    ssize_t n = write((*it).second->getFirstClient(), &input, sizeof(input));
    n = write((*it).second->getSecondClient(), &input, sizeof(input));
  }

  exit(0);
}

void *Server::shouldStop(void *serv) {
  Server *server = (Server *) serv;
  string exit;
  cout << "Type 'exit' to close the server." << endl;
  while (true) {
    cin.clear();
    cin >> exit;
    if (exit == "exit") {
      server->stop();
      break;
    }
  }
}
