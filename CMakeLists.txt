cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)

add_executable(Client
        src/client/board.cpp
        src/client/board.h
        src/client/cell.cpp
        src/client/cell.h
        src/client/client.cpp
        src/client/client.h
        src/client/computer.cpp
        src/client/computer.h
        src/client/consoleDisplay.cpp
        src/client/consoleDisplay.h
        src/client/display.h
        src/client/dummy.cpp
        src/client/dummy.h
        src/client/gameFlow.cpp
        src/client/gameFlow.h
        src/client/human.cpp
        src/client/human.h
        src/client/logic.cpp
        src/client/logic.h
        src/client/main.cpp
        src/client/player.cpp
        src/client/player.h
        src/client/point.cpp
        src/client/point.h
        src/client/regLogic.cpp
        src/client/regLogic.h src/server/commands/command.h src/server/commands/commandStart.cpp src/server/commands/commandStart.h src/server/commands/commandJoin.cpp src/server/commands/commandJoin.h src/server/commands/commandClose.cpp src/server/commands/commandClose.h src/server/commands/commandPrint.cpp src/server/commands/commandPrint.h src/client/gameManager.cpp src/client/gameManager.h src/server/commands/commandsManager.cpp src/server/commands/commandsManager.h)

add_executable(Server
        src/server/main.cpp
        src/server/server.cpp
        src/server/server.h src/server/Room.cpp src/server/Room.h src/server/Lobby.cpp src/server/Lobby.h src/server/HandleGame.h src/server/HandleGame.cpp)