#include <cstring>
#include <unistd.h>
#include <iostream>
#include "clientCommand.h"
#include "../tools.h"


ClientCommand::ClientCommand(int clientSocket) : clientSocket_(clientSocket) {}

int ClientCommand::activate(string command) {
  char buffer[BUFFER];
  memset(buffer, 0, sizeof(buffer));
  ssize_t n;

  if (strcmp(command.c_str(), "list_games") == 0) {
    getGameList();
    return -1;
  }
  string firstWord = command.substr(0, command.find(" "));

  if (strcmp(firstWord.c_str(), "start") == 0) {
    // start() return false if the room is taken. in that case return
    if (!start(command.substr(command.find(" "), command.size()))) {
      return -1;
    }
    n = read(clientSocket_, &buffer, sizeof(buffer));
    if (strcmp(buffer, "1") == 0) {
      return 1;
    } else if (strcmp(buffer, "0") == 0) {
      return 0;
    }
    return -1;
  }

  if (strcmp(firstWord.c_str(), "join") == 0) {
    if (!join(command.substr(command.find(" "), command.size()))) {
      return -1;
    }
    n = read(clientSocket_, &buffer, sizeof(buffer));
    cout << "index is: " << buffer << endl;
    if (strcmp(buffer, "1") == 0) {
      return 1;
    } else if (strcmp(buffer, "0") == 0) {
      return 0;
    }
  }

  cout << "\'" << command << "\' is not a valid command." << endl;
  return -1;
}

//asks the list of games from the server and prints them
void ClientCommand::getGameList() {
  char buffer[BUFFER];
  strcpy(buffer, "list_games");
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  cout << "Waiting for list of games from server" << endl;
  n = read(clientSocket_, &buffer, sizeof(buffer));
  cout << "Available rooms: " << buffer;
}

//asks the server to start room "name"
bool ClientCommand::start(string name) {
  char buffer[BUFFER];
  string startString = "start" + name;
  strcpy(buffer, startString.c_str());
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  n = read(clientSocket_, &buffer, sizeof(buffer));
  if (strcmp(buffer, "-1") == 0) {
    cout << "room is already taken." << endl;
    return false;
  }
  cout << buffer << "waiting for the second client, don't leave!" << endl;
  return true;
}

bool ClientCommand::join(string name) {
  char buffer[BUFFER];
  string joinString = "join" + name;
  strcpy(buffer, joinString.c_str());
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  n = read(clientSocket_, &buffer, sizeof(buffer));
  if (strcmp(buffer, "-1") == 0) {
    cout << "room is not available" << endl;
    return false;
  }
  cout << "recieved from server: " << endl;
  return true;
}
