cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 98)

set(CLIENT
        src/client/board.cpp
        src/client/board.h
        src/client/cell.cpp
        src/client/cell.h
        src/client/client.cpp
        src/client/client.h
        src/client/clientCommand.cpp
        src/client/clientCommand.h
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
        src/client/regLogic.h
        src/tools.h)
set(SERVER
        src/server/command.h
        src/server/commandClose.cpp
        src/server/commandClose.h
        src/server/commandJoin.cpp
        src/server/commandJoin.h
        src/server/commandPrint.cpp
        src/server/commandPrint.h
        src/server/commandsManager.cpp
        src/server/commandsManager.h
        src/server/commandStart.cpp
        src/server/commandStart.h
        src/server/HandleGame.cpp
        src/server/HandleGame.h
        src/server/Lobby.cpp
        src/server/Lobby.h
        src/server/main.cpp
        src/server/Room.cpp
        src/server/Room.h
        src/server/server.cpp
        src/server/server.h src/server/Task.cpp src/server/Task.h src/server/ThreadPool.cpp src/server/ThreadPool.h)

add_executable(client ${CLIENT})
add_executable(server ${SERVER})