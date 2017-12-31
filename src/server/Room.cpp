#include "Room.h"

const string &Room::getName() const {
  return name_;
}

void Room::setName(const string name) {
  name_ = name;
}

int Room::getFirstClient() const {
  return firstClient_;
}

void Room::setFirstClient(int firstClient) {
  firstClient_ = firstClient;
}

int Room::getSecondClient() const {
  return secondClient_;
}

void Room::setSecondClient(int secondClient) {
  secondClient_ = secondClient;
}

int Room::getThreadID() const {
  return threadID_;
}

void Room::setThreadID(int threadID) {
  threadID_ = threadID;
}

Status Room::getStatus() const {
  return status_;
}

void Room::setStatus(Status status) {
  status_ = status;
}

Room::Room() {
  status_ = Ended;
  threadID_ = 0;
  secondClient_ = 0;
  firstClient_ = 0;
  name_ = "";
}
