#include <map>
#include "commandJoin.h"
void CommandJoin::execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket) {
  string name = args[0];
  if (lobby.find(name) == lobby.end()) {
    // not found
  } else {
    lobby[name]->firstClient = clientSocket;
    lobby[name]->status = Active;
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *args);
  }
}