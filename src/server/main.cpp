#include "server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
  char settings[] = "/home/h/CLionProjects/Reversi/src/server/settings";
  Server server(settings);
  try {
    server.start();
  } catch (const char *msg) {
    cout << "Cannot start server. Reason: " << msg << endl;
    exit(-1);
  }
}