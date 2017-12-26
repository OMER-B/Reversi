#include "Room.h"

Room::Room() {

}

const string &Room::getName() const {
  return name_;
}

void Room::setName(const string &name) {
  name_ = name_;
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
