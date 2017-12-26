#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include <arpa/inet.h>
#include <sstream>
#include <thread>

#define BUFFER 256
#define MAX_CONNECTED_CLIENTS 5

using namespace std;

Server::Server(int port) : serverSocket_(0) {
  port_ = port;
  lobby_ = new Lobby;
  threads_ = new vector<pthread_t*>;
  handleGame_ = new HandleGame;
  manager_ = new CommandsManager(lobby_, handleGame_);
}

Server::Server(char *fileName) {
  threads_ = new vector<pthread_t*>;
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
  listen(serverSocket_, MAX_CONNECTED_CLIENTS);
  // Define the client socket's structures
  struct sockaddr_in clientAddress;
  socklen_t clientAddressLen;

  //thread main process with (if == exit) ((FOR SERVER)))
  //TODO create here new thread, that gets all the server parameters in "first thread args"

  while (true) {
    // Accept a new clients connections.
    int clientSocket = accept(serverSocket_,
                                   (struct sockaddr *) &clientAddress,
                                   &clientAddressLen);
    cout << "First client connected" << endl;
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

static void* handleClient(void * args) {
  SecondThreadArgs *clientArgs = (SecondThreadArgs*)args;
  CommandsManager *manager = clientArgs->manager;

  char input[BUFFER];
  memset(input, 0, sizeof(input));

  cout << "connected to client: " <<clientArgs->clientSocket << endl;

  ssize_t n = read(clientArgs->clientSocket, &input, sizeof(input));

  string command;
  vector<string> stringArgs;
  command = seperate(input).first;
  stringArgs = seperate(input).second;

  manager->executeCommand(command, stringArgs, clientArgs->clientSocket);
  //TODO: close thread here
}

static std::pair<string, vector<string> > seperate(string input) {
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