//
// Created by h on 26/12/17.
//

#include "Lobby.h"

Lobby::Lobby() {
  lobby_ = new map<string, Room *>();
}

Lobby::~Lobby() {
  delete lobby_;
}

vector<string> Lobby::getListOfRooms() {
  vector<string> listOfRooms;
  for (map<string, Room *>::iterator it = lobby_->begin(); it != lobby_->end(); ++it) {
    listOfRooms.push_back(it->first);
  }
  return listOfRooms;
}

bool Lobby::contains(string name) {
  return !(lobby_->find(name) == lobby_->end());
}

void Lobby::removeRoom(string name) {
  lobby_->erase(name);
}

void Lobby::addRoom(Room &room) {
  string name = room.getName();
  lobby_->at(name) = &room;
}

Room *Lobby::getRoom(string name) {
  return lobby_[name];
}
