//
// Created by h on 27/12/17.
//

#include <cstring>
#include <unistd.h>
#include <iostream>
#include "clientCommand.h"
#define BUFFER_SIZE 128

ClientCommand::ClientCommand(int clientSocket) : clientSocket_(clientSocket) {}

int ClientCommand::activate(string command) {
  char buffer[BUFFER_SIZE];
  memset(buffer, 0, sizeof(buffer));
  ssize_t n;
  if (strcmp(command.c_str(), "list_games") == 0) {
    getGameList();
    return -1;
  }
  string firstWord = command.substr(0, command.find(" "));
  if (strcmp(firstWord.c_str(), "start") == 0) {
    start(command.substr(command.find(" "), command.size()));
    n = read(clientSocket_, &buffer, sizeof(buffer));
    if (strcmp(buffer, "1") == 0) {
      return 1;
    } else if (strcmp(buffer, "0") == 0) {
      return 0;
    }
    return -1;
  }
  if (strcmp(firstWord.c_str(), "join") == 0) {
    join(command.substr(command.find(" "), command.size()));
    n = read(clientSocket_, &buffer, sizeof(buffer));
    if (strcmp(buffer, "1") == 0) {
      return 1;
    } else if (strcmp(buffer, "0") == 0) {
      return 0;
    }
    return -1;
  }
  cout << "\'" << command << "\' is not a valid command." << endl;
  return -1;
}

void ClientCommand::getGameList() {
  char buffer[BUFFER_SIZE];
  strcpy(buffer, "list_games");
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  cout << "Waiting for list of games from server" << endl;
  n = read(clientSocket_, &buffer, sizeof(buffer));
  cout << "Available rooms: " << buffer;
}

void ClientCommand::start(string name) {
  char buffer[BUFFER_SIZE];
  string startString = "start" + name;
  strcpy(buffer, startString.c_str());
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  cout << "Trying to open a new room:" << name << endl;
  n = read(clientSocket_, &buffer, sizeof(buffer));
  cout << name << ": " << buffer;

}

void ClientCommand::join(string name) {
  char buffer[BUFFER_SIZE];
  string joinString = "join" + name;
  strcpy(buffer, joinString.c_str());
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  cout << "Trying to join room" << name << endl;
  n = read(clientSocket_, &buffer, sizeof(buffer));
  cout << buffer;
  //TODO server will send index of player
}

/**
 * void Client::getFeedback() {
  char feedback[BUFFER];
  ssize_t n = read(clientSocket_, &feedback, sizeof(feedback));
  if (n == -1) {
    throw "Error reading enemy point from socket";
  }
  cout << feedback;
}
 */
