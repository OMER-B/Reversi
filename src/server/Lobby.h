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

  // Removes a room from the lobby.
  void removeRoom(string name);

  // Returns a list of all waiting rooms.
  vector<string> getListOfRooms();

  // Checks if a room name already exists.
  bool contains(string name);

  // Returns room by name.
  Room *getRoom(string name);

  // Creates a new room with input name.
  Room *createRoom(string name);

  // Returns the map of the rooms.
  map<string, Room *> *getMap();
};

#endif //REVERSI_LOBBY_H
