#include <istream>
#include <cstdlib>
#include "client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <limits>
#include <fstream>

#define BUFFER 128

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

int Client::connectToServer() {
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
  cout << "Connected to server. IP: " << serverIP_ << ", Port: " << serverPort_
       << "." << endl << "Waiting for second player." << endl;
  getCommand();
}

string Client::getCommand() {
  char command[BUFFER] = "";
  cin.ignore();
  cin.clear();
  cin.getline(command, sizeof(command));
  ssize_t n = write(clientSocket_, &command, sizeof(command));
  if (n == -1) {
    throw "failed to write to server";
  }
  cout << "command: " << command << endl;
}



int Client::makeMove(Board &board, Logic &logic, Display &display) {
  char move[BUFFER] = "";
  ssize_t n;
  Point newCell = Client::getInput(board, logic, display);

  if (newCell == Point(0, 0)) {
    strcpy(move, "0 0");
    n = write(clientSocket_, &move, sizeof(move));
    cout << endl << "You have ended the game." << endl;
    return 2;
  } else if (newCell == Point(-1, -1)) {
    strcpy(move, "-1 -1");
    n = write(clientSocket_, &move, sizeof(move));
    int enemyStatus = getRemoteEnemyMovement();
    if ((enemyStatus == 1) || (enemyStatus == 2)) {
      cout << endl << "Both players don't have any moves." << endl;
      return 2;
    }
  } else {
    logic.putNewCell(board, *this, newCell);
    display.printBoard(&board);
    strcpy(move, newCell.toString().c_str());
    // Write the points to the socket
    n = write(clientSocket_, &move, sizeof(move));
    if (n == -1) {
      throw "Error input point to socket";
    }
  }

  if (getRemoteEnemyMovement() == 2) {
    cout << endl << "Other player has ended the game." << endl;
    return 2;
  }
  return 0;
}

int Client::getRemoteEnemyMovement() {
  cout << "It's enemy's turn. Waiting their input." << endl;
  // Read other player's move from the server
  char enemyString[10];
  ssize_t n = read(clientSocket_, &enemyString, sizeof(enemyString));
  if (n == -1) {
    throw "Error reading enemy point from socket";
  }
  Point point = Point(enemyString);
  dummy_->setEnemyPoint(point);
  if (point.getX() == 0) {
    return 2;
  }
  if (point.getX() == -1) {
    return 1;
  }
  return 0;
}

Point Client::getInput(Board &board, Logic &logic, Display &display) {
  cout << getSymbol() << ", it's your turn." << endl;
  vector<Point> possibleMoves = logic.getOptionalMoves(board, *this);
  if (possibleMoves.empty()) {
    cout << "You don't have any moves. Type -1." << endl
         << "If enemy did not make a move type 0." << endl;
  } else {
    cout << "Possible moves: ";
    for (vector<Point>::iterator it = possibleMoves.begin();
         it != possibleMoves.end(); ++it) {
      cout << *it;
    }
  }
  int moveX = -1, moveY = -1;
  while (true) {
    cout << endl << "Enter your move 'row col': ";
    cin >> moveX;
    if (moveX == 0) {
      return Point(0, 0);
    }
    if (moveX == -1) {
      return Point(-1, -1);
    }
    cin >> moveY;

    // Check if input is an integer.
    if (cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Minus one for indexes.
    moveX--;
    moveY--;
    if (board.inBoundaries(moveX, moveY)
        && logic.isOptionInList(Point(moveX, moveY), possibleMoves)) {
      break;
    }
  }

  return Point(moveX, moveY);
}

int Client::setUp() {
  int turn;
  char c = 'O';
  ssize_t n = read(clientSocket_, &turn, sizeof(turn));
  if (n == -1) {
    throw "Error reading enemy point from socket";
  }

  if (turn == 0) {
    c = 'X';
    dummy_->Dummy::setSymbol('O');
  } else {
    dummy_->Dummy::setSymbol('X');
  }

  cout << "Game has started. You are: " << c << " (" << turn << ")" << endl;
  cout << "To end the game, send 0." << endl;
  cout << "To announce no more moves, send -1." << endl;
  Client::setSymbol(c);
  return turn;
}

Dummy *Client::getDummy() {
  return dummy_;
}

void Client::setDummy_(Dummy *dummy) {
  dummy_ = dummy;
}
