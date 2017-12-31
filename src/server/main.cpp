#include "server.h"
using namespace std;
int main() {
  char settings[] =
      "/home/omer/Desktop/לימודים/שנה ב/תכנות מתקדם 1/Reversi/src/server/settings";
  Server server(settings);
  try {
    server.start();
  } catch (const char *msg) {
    cout << "Cannot start server. Reason: " << msg << endl;
    exit(-1);
  }
}