#include "server.h"
using namespace std;
int main() {
  char settings[] = "server_config";
  Server server(settings);
  try {
    server.start();
  } catch (const char *msg) {
    cout << "Cannot start server. Reason: " << msg << endl;
    return -1;
  }
}