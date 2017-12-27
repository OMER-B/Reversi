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
  if (strcmp(command.c_str(), "list_games")==0) {
    getGameList();
    return false;
  }
  string firstWord = command.substr(0, command.find(" "));
  if (strcmp(firstWord.c_str(), "start") == 0) {
    start(command.substr(command.find(" "), command.size()));
    //wait to get an approval from server!
    //update client to be the first player
    return true;
  }
  if (strcmp(firstWord.c_str(), "join") == 0) {
    join(command.substr(command.find(" "), command.size()));
    //update client to be second
    return true;
  }
}

void ClientCommand::getGameList() {
  char buffer[BUFFER_SIZE];
  strcpy(buffer,"list_games");
  ssize_t n = write(clientSocket_, &buffer, sizeof(buffer));
  cout << "waiting for list of games from server" << endl;
  n = read(clientSocket_, &buffer, sizeof(buffer));
  cout << "games: " << buffer;
}

void ClientCommand::start(string name) {

}

void ClientCommand::join(string name) {

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
