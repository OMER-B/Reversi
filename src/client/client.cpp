#include <iostream>
#include "client.h"
#include "clientCommand.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

#define BUFFER 128

/**
 * 1. connect to server, here
 * 2. send a command, here
 * 3. a class to handle the command:
 *      a. if he wants the list of games: read from socket
 *      b. if he wants to start a new game: wait for someone to join
 *      c. if he wants to join a game: go to set up and run from gameflow
 * 4. return here in a loop, until "close"
 *
 */


using namespace std;

Client::Client(char *serverIP, int serverPort)
    : Human('R'),
      serverIP_(serverIP),
      serverPort_(serverPort),
      clientSocket_(0) {
  dummy_ = NULL;
}

Client::Client(char *fileName) : Human('R'),
                                 serverIP_(),
                                 serverPort_(), clientSocket_(0) {
  string input;
  ifstream inFile;
  inFile.open(fileName);
  inFile >> input;
  serverIP_ = input;
  inFile >> input;
  serverPort_ = atoi(input.c_str());
  inFile.close();
  dummy_ = NULL;
}

Client::~Client() {
  close(clientSocket_);
}

void Client::connectToServer() {
  // Create a socket point
  clientSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket_ == -1) {
    throw "Error opening socket";
  }

  // Convert the ip string to a network address
  struct in_addr address;
  if (!inet_aton(serverIP_.c_str(), &address)) {
    throw "Can't parse IP address. IP is probably in wrong format.";
  }

  // Get a hostent structure for the given host address
  struct hostent *server;
  server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
  if (server == NULL) {
    throw "Host is unreachable. Server may be offline.";
  }

  // Create a structure for the server address
  struct sockaddr_in serverAddress;
  bzero((char *) &address, sizeof(address));
  serverAddress.sin_family = AF_INET;
  memcpy((char *) &serverAddress.sin_addr.s_addr,
         server->h_addr,
         server->h_length);

  // htons converts values between host and network byte orders
  serverAddress.sin_port = htons(serverPort_);

  // Establish a connection with the TCP server
  if (connect(clientSocket_, (struct sockaddr
  *) &serverAddress, sizeof(serverAddress)) == -1) {
    throw "Error connecting to server";
  }
}

int Client::indexOfPlayer() {
  ClientCommand clientCommand(clientSocket_);
  string command;
  int index;
  do {
    cout << "Enter command:" << endl
         << "'start <room>', 'join <room>' or 'list_games'" << endl;
    command = getCommand();
    index = clientCommand.activate(command);
    if (index != -1) {
      setUp(index);
      return index;
    }
  } while ((strcmp(command.c_str(), "close") != 0)
      && (strcmp(command.c_str(), "exit") != 0));
  return -1;
}

string Client::getCommand() {
  char command[BUFFER] = "";
  cin.clear();
  cin.getline(command, sizeof(command));
  return string(command);
}

int Client::makeMove(Board &board, Logic &logic, Display &display) {
  ssize_t n;
  char serverAnswer[BUFFER];
  n = read(clientSocket_, &serverAnswer, sizeof(serverAnswer));
  char input[BUFFER];
  memset(input, 0, sizeof(input));

  Human::getInput(board, logic, display, input);

  if (strcmp(input, "close") == 0) {
    n = write(clientSocket_, &input, sizeof(input));
    cout << endl << "You have ended the game." << endl;
    close(clientSocket_);
    return 2;
  }

  if (strcmp(input, "nomoves") == 0) {
    n = write(clientSocket_, &input, sizeof(input));
    return 1;
  } else {

    Point newCell = Point(input).decrease();
    logic.putNewCell(board, *this, newCell);
    display.printBoard(&board);
    // Write the points to the socket
    n = write(clientSocket_, &input, sizeof(input));
  }
  return 0;
}

void Client::setUp(int index) {
  char symbol[] = {'X', 'O'};

  dummy_->Dummy::setSymbol(symbol[1 - index]);

  Client::setSymbol(symbol[index]);

  cout << "Game has started. You are: " << symbol[index] << " (" << index << ")"
       << endl;

}

Dummy *Client::getDummy() {
  return dummy_;
}

void Client::setDummy_(Dummy *dummy) {
  dummy_ = dummy;
}

int Client::getClientSocket_() const {
  return clientSocket_;
}
