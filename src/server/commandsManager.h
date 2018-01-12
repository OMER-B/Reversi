#ifndef REVERSI_COMMANDSMANAGER_H
#define REVERSI_COMMANDSMANAGER_H

#include <map>
#include "command.h"
#include "commandJoin.h"
#include "commandStart.h"
#include "commandClose.h"
#include "commandPrint.h"
#include "HandleGame.h"
#include "Lobby.h"
#include "ThreadPool.h"

class CommandsManager { // class is singleton
 private:
  // A map of all commands to acces in O(1).
  map<string, Command *> commandsMap_;

  // Instance of itself for singleton design pattern.
  static CommandsManager *instance_;

  // list of threads for join command.
  ThreadPool *pool_;

  //Constructor for CommandsManager.
  CommandsManager(Lobby *, HandleGame *, ThreadPool *pool);

 public:
  // Command manager is a singleton. getInstance() calls the constructor if no instance exists, and returns the existing one if does.
  static CommandsManager *getInstance(Lobby *,
                                      HandleGame *,
                                      ThreadPool *pool);

  // Command manager is a singleton. getInstance() calls the constructor if no instance exists, and returns the existing one if does.
  static CommandsManager *getInstance();

  // Checks if an input command is legal.
  bool isLegalCommand(string command, int client);

  // Calls the execute() method of commands.
  bool executeCommand(string command, string arg, int client);

  // Seperates input to two strings by space.
  std::pair<string, string> seperate(string input);
  ~CommandsManager();
};

#endif //REVERSI_COMMANDSMANAGER_H