cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googlemock/include)
include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES
        board.cpp
        board.h
        cell.cpp
        cell.h
        computer.cpp
        computer.h
        consoleDisplay.cpp
        consoleDisplay.h
        display.h
        game.cpp
        game.h
        human.cpp
        human.h
        logic.cpp
        logic.h
        main.cpp
        player.cpp
        player.h
        point.cpp
        point.h
        regLogic.cpp
        regLogic.h tests/boardTest.cpp tests/playerTest.cpp tests/pointTest.cpp tests/cellTest.cpp tests/logicTest.cpp server.cpp server.h)

add_executable(Reversi ${SOURCE_FILES} tests/boardTest.cpp tests/playerTest.cpp tests/cellTest.cpp tests/logicTest.cpp server.cpp server.h)
target_link_libraries(Reversi gtest gtest_main)
