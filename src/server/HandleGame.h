//
// Created by h on 26/12/17.
//

#ifndef REVERSI_HANDLEGAME_H
#define REVERSI_HANDLEGAME_H

#include <string>
#include "Room.h"

class HandleGame {
 public:
  
  // This is the read/write game loop.
  static void *play(void *room);
};

#endif //REVERSI_HANDLEGAME_H
