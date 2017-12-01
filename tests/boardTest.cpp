#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../board.h"
#include "../human.h"

using testing::Eq;

namespace {
class boardTest : public testing::Test {
 protected:
  Board *board;
  Player *players[2];

 public:
  boardTest() {
    players[0] = new Human('X');
    players[1] = new Human('O');
    board = new Board(8, 8, players);
  }

  ~boardTest() {
    delete players[0];
    delete players[1];

    delete board;
  }
};
}

// Tests if the size of the board is assigned correctly.
TEST_F(boardTest, WorksIfSizeCorrect) {
  EXPECT_EQ(8, board->getX());
  EXPECT_EQ(8, board->getY());
}

// Tests if the inBoundaries() function works correctly.
TEST_F(boardTest, InBoundariesWorks) {
  Point point(3, 5);
  board->fillCell(point, players[0]);
  Cell cell(point);

  EXPECT_EQ(board->getCell(point), board->getCell(3, 5));
  EXPECT_EQ(cell, *board->getCell(3, 5));
  EXPECT_EQ(cell, *board->getCell(point));
  EXPECT_TRUE(board->inBoundaries(point));
  EXPECT_TRUE(board->inBoundaries(3, 5));
  EXPECT_FALSE(board->inBoundaries(9, 9));
  EXPECT_FALSE(board->inBoundaries(-1, 5));
}

// Tests if the different ways to get a player from the board works.
TEST_F(boardTest, GetPlayerWorks) {
  Point point(3, 5);
  board->fillCell(point, players[0]);

  EXPECT_EQ(players[0], board->getPlayer(point));
  EXPECT_EQ(players[0]->getSymbol(), board->getPlayer(point)->getSymbol());
  EXPECT_EQ(players[0], board->getPlayer(3, 5));
}

// Works if the board knows it is full.
TEST_F(boardTest, isFullWorking) {
  EXPECT_FALSE(board->isFull());

  for (int i = 0; i < board->getX(); i++) {
    for (int j = 0; j < board->getY(); j++) {
      board->fillCell(Point(i, j), players[0]);
    }
  }

  EXPECT_TRUE(board->isFull());
}
