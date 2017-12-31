

#ifndef REVERSI_ROOM_H
#define REVERSI_ROOM_H

#include <string>

using namespace std;

typedef enum Status { Waiting, Active, Ended } Status;

class Room {
 private:
  string name_;
  int firstClient_, secondClient_, threadID_;
  Status status_;

 public:

  Room();

  // Returns room name.
  const string &getName() const;

  // Sets room name.
  void setName(const string name);

  // Returns first client of the room.
  int getFirstClient() const;

  // Sets first client of the room.
  void setFirstClient(int firstClient);

  // Returns second client of the room.
  int getSecondClient() const;

  // Sets second client of the room.
  void setSecondClient(int secondClient);

  int getThreadID() const;

  void setThreadID(int threadID);

  // Returns room status.
  Status getStatus() const;

  // Sets room status.
  void setStatus(Status status);
};

#endif //REVERSI_ROOM_H
