

#ifndef REVERSI_ROOM_H
#define REVERSI_ROOM_H


#include <string>

using namespace std;

typedef enum Status { Waiting, Active, Ended } Status;

class Room {
private:
  string name_;
  int firstClient_ , secondClient_ , threadID_;
  Status status_;

public:

  Room();
  const string &getName() const;

  void setName(const string name);

  int getFirstClient() const;

  void setFirstClient(int firstClient);

  int getSecondClient() const;

  void setSecondClient(int secondClient);

  int getThreadID() const;

  void setThreadID(int threadID);

  Status getStatus() const;

  void setStatus(Status status);
};


#endif //REVERSI_ROOM_H