//
// Created by h on 26/12/17.
//

#ifndef REVERSI_LOBBY_H
#define REVERSI_LOBBY_H

#include <vector>
#include <map>
#include "Room.h"

class Lobby {
 private:
  map<string, Room *> *roomsMap_;

 public:
  Lobby();
  ~Lobby();
  bool isEmpty();
  void addRoom(Room &room);
  void removeRoom(string name);
  vector<string> getListOfRooms();
  bool contains(string name);
  Room *getRoom(string name);

  Room *createRoom(string name);
  map<string, Room *> *getMap();
};

#endif //REVERSI_LOBBY_H
