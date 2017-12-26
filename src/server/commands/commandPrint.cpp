#include <unistd.h>
#include "commandPrint.h"
void CommandPrint::execute(vector<string> &args, int clientSocket) {
  string listOfGames;
  cout << "Sending list of games to socket: " << clientSocket << endl;
  //ssize_t n = write(clientSocket, &listOfGames, listOfGames.size());
}