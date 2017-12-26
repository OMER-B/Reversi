//
// Created by h on 26/12/17.
//

#ifndef REVERSI_HANDLEGAME_H
#define REVERSI_HANDLEGAME_H


#include <string>

typedef enum Status { Waiting, Active, Ended };

typedef struct Room {
  std::string name;
  int firstClient;
  int secondClient;
  int threadID;
  Status status_;
} Room;

class HandleGame {
public:
  static void play(Room *room);
};


#endif //REVERSI_HANDLEGAME_H
