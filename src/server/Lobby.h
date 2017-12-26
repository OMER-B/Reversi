//
// Created by h on 26/12/17.
//

#ifndef REVERSI_LOBBY_H
#define REVERSI_LOBBY_H

#include <map>
#include "server.h"
#include "Room.h"

class Lobby {
private:
  map<string, Room *> *lobby_;

public:
  Lobby();
  ~Lobby();
  void addRoom(Room &room);
  void removeRoom(string name);
  vector<string> getListOfRooms();
  bool contains(string name);
  Room* getRoom(string name);
};


#endif //REVERSI_LOBBY_H
