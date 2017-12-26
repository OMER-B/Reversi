

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

  const string &getName() const;

  void setName(const string &name_);

  int getFirstClient() const;

  void setFirstClient(int firstClient_);

  int getSecondClient() const;

  void setSecondClient(int secondClient_);

  int getThreadID() const;

  void setThreadID(int threadID_);

  Status getStatus() const;

  void setStatus(Status status);
};


#endif //REVERSI_ROOM_H
