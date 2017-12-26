//
// Created by h on 26/12/17.
//

#include "Lobby.h"

Lobby::Lobby() {
  roomsMap_ = new map<string, Room *>();
}

Lobby::~Lobby() {
  delete roomsMap_;
}

vector<string> Lobby::getListOfRooms() {
  vector<string> listOfRooms;
  for (map<string, Room *>::iterator it = roomsMap_->begin(); it != roomsMap_->end(); ++it) {
    listOfRooms.push_back(it->first);
  }
  return listOfRooms;
}

bool Lobby::contains(string name) {
  return !(roomsMap_->find(name) == roomsMap_->end());
}

void Lobby::removeRoom(string name) {
  roomsMap_->erase(name);
}

void Lobby::addRoom(Room &room) {
  string name = room.getName();
  roomsMap_->at(name) = &room;
}

Room *Lobby::getRoom(string name) {
  return roomsMap_->at(name);
}

Room* Lobby::createRoom(string name) {
  Room * room = new Room();
  roomsMap_->at(name) = room;
  return room;
}