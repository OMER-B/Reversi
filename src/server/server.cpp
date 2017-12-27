#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <arpa/inet.h>
#include <sstream>
#include <pthread.h>


using namespace std;

static void *acceptClients(void *args);

static void *handleClient(void *args);

static pair<string, vector<string> > seperate(string input);

Server::Server(int port) : serverSocket_(0) {
  port_ = port;
  lobby_ = new Lobby;
  threads_ = new vector<pthread_t *>;
  handleGame_ = new HandleGame;
  manager_ = new CommandsManager(lobby_, handleGame_);
}

Server::Server(char *fileName) {
  threads_ = new vector<pthread_t *>;
  lobby_ = new Lobby;
  handleGame_ = new HandleGame;
  manager_ = new CommandsManager(lobby_, handleGame_);

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
  cout << "Binding succeeded." << endl;
  // Start listening to incoming connections
//  listen(serverSocket_, MAX_CONNECTED_CLIENTS);
//  // Define the client socket's structures
//  struct sockaddr_in clientAddress[MAX_CONNECTED_CLIENTS];
//  socklen_t clientAddressLen[MAX_CONNECTED_CLIENTS];


  FirstThreadArgs args1;
  args1.serverSocket = serverSocket_;
  args1.manager = manager_;
  args1.threads = threads_;

  pthread_t id;
  threads_->push_back(&id);
  pthread_create(&id, nullptr, acceptClients, (void *) &args1);

  string exit;
  cin >> exit;
  if (strcmp(exit.c_str(), "exit")) {
    for (vector<pthread_t *>::iterator it = threads_->begin();
         it != threads_->end(); ++it) {
      pthread_exit(*it);
    }
  }

}

void *acceptClients(void *args) {

  FirstThreadArgs *args1 = (FirstThreadArgs *) args;
  int serverSocket = args1->serverSocket;

  vector<pthread_t *> *threads = args1->threads;
  CommandsManager *manager = args1->manager;

  listen(serverSocket, MAX_CONNECTED_CLIENTS);
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLen;

  while (true) {
    // Accept a new clients connections.
    int clientSocket = accept(serverSocket,
                              (struct sockaddr *) &clientAddress,
                              &clientAddressLen);
    cout << "First client connected" << endl;
    if (clientSocket == -1) {
      throw "Error on first client accept";
    }
    SecondThreadArgs args;
    args.clientSocket = clientSocket;
    args.manager = manager;
    pthread_t id;
    threads->push_back(&id);
    pthread_create(&id, NULL, handleClient, &args);
  }
}

void *handleClient(void *args) {
  SecondThreadArgs *clientArgs = (SecondThreadArgs *) args;
  CommandsManager *manager = clientArgs->manager;

  char input[BUFFER];
  memset(input, 0, sizeof(input));

  cout << "connected to client: " << clientArgs->clientSocket << endl;

  ssize_t n = read(clientArgs->clientSocket, &input, sizeof(input));
  if (n == -1) {
    throw "failed to receive read from client";
  }
  vector<string> stringArgs;

  pair<string, vector<string> > result;
  result = seperate(input);
  
  string command = result.first;
  stringArgs = result.second;

  manager->executeCommand(command, stringArgs, clientArgs->clientSocket);
  //TODO: close thread here
}

std::pair<string, vector<string> > seperate(string input) {
  stringstream stream(input);
  string command;
  string buffer;
  vector<string> args;

  stream >> command;
  while (stream >> buffer) {
    args.push_back(buffer);
  }
  return pair<string, vector<string> >(command, args);
}

Server::~Server() {
  delete threads_;
  delete lobby_;
  delete manager_;
  delete handleGame_;
  stop();
}

void Server::stop() {
  close(serverSocket_);
}