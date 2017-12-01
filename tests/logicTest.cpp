#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../board.h"
#include "../logic.h"
#include "../human.h"
#include "../regLogic.h"
#include "../consoleDisplay.h"

using testing::Eq;

class logicTest : public testing::Test {
 protected:
  Logic *logic;
  Board *board;
  Player *players[2];
  Player *player1, *player2;

 public:
  logicTest() {
    player1 = new Human('x');
    player2 = new Computer('o');
    players[0] = player1;
    players[1] = player2;
    board = new Board(8, 8, players);
    logic = new RegLogic();
  }
  ~logicTest() {
    delete player1;
    delete player2;
    delete board;
    delete logic;
  }
};

// Tests if putNewCell() function actually puts a cell on the board.
TEST_F(logicTest, putNewCellWorks) {
  Point point(3, 2);

  EXPECT_TRUE(board->getCell(point)->isEmpty());
  logicTest::logic->putNewCell(*board, *player1, point);
  EXPECT_FALSE(board->getCell(point)->isEmpty());
}

// Tests if you get all possible move from getOptionalMoves() function.
TEST_F(logicTest, getOptionalMovesWorks) {
  // put two new cells
  logic->putNewCell(*board, *player1, Point(3, 2));
  logic->putNewCell(*board, *player2, Point(3, 5));

  vector<Point> moves = logic->getOptionalMoves(*board, *player2);

  // Check if the vector size is actually 4 and the check if all the 4 elements are correct.
  EXPECT_TRUE(moves.size() == 4);
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(3, 1)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(2, 2)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(2, 4)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(4, 2)) != moves.end());
}

// Checks if a cell has been flipped after flipCell() is called.
TEST_F(logicTest, flipCellsWorks) {

  EXPECT_EQ(player1, board->getCell(3, 4)->getPlayer());
  vector<Point> moves;
  moves.push_back(Point(3, 4));
  logic->flipCells(*board, moves, *player2);
  EXPECT_FALSE(player1 == board->getCell(3, 4)->getPlayer());
  EXPECT_TRUE(player2 == board->getCell(3, 4)->getPlayer());
}

// Works if all the players cells are returned.
TEST_F(logicTest, getPlayerCellsWorks) {
  logic->putNewCell(*board, *player1, Point(6, 2));
  logic->putNewCell(*board, *player1, Point(5, 2));
  logic->putNewCell(*board, *player1, Point(4, 2));
  logic->putNewCell(*board, *player1, Point(3, 2));

  vector<Point> moves = logic->getPlayerCells(*board, *player1);

  // checks if all the cells are correct.
  EXPECT_TRUE(moves.size() == 7);
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(3, 2)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(3, 3)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(3, 4)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(4, 2)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(5, 2)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(6, 2)) != moves.end());
  EXPECT_TRUE(
      std::find(moves.begin(), moves.end(), Point(4, 3)) != moves.end());

  // checks if all the players in the vector are the actual player.
  for (int i = 0; i < moves.size(); i++) {
    EXPECT_EQ(player1, board->getPlayer(moves.at(i)));
  }
}

// Works if a score of player is updated before and after function call.
TEST_F(logicTest, updateScoreWorks) {

  EXPECT_EQ(player1->getScore(), 2);
  EXPECT_EQ(player2->getScore(), 2);

  // should remove 1 score from player1 and add it to player2.
  logic->updateScore(player1, player2);

  EXPECT_EQ(player1->getScore(), 1);
  EXPECT_EQ(player2->getScore(), 3);
}

// Works if a two directions flip works.
TEST_F(logicTest, flipTwoDirectionsWork) {

  logic->putNewCell(*board, *player1, Point(3, 2));
  logic->putNewCell(*board, *player2, Point(4, 2));
  logic->putNewCell(*board, *player1, Point(5, 3));

  EXPECT_EQ(player1, board->getPlayer(3, 3));
  EXPECT_EQ(player1, board->getPlayer(3, 4));

  // this new cell should flip 2 cells in different directions.
  logic->putNewCell(*board, *player2, Point(2, 4));
  EXPECT_EQ(player2, board->getPlayer(3, 3));
  EXPECT_EQ(player2, board->getPlayer(3, 4));
}

// Works if AI places in the best position.
TEST_F(logicTest, greedyAIWorks) {
  logic->putNewCell(*board, *player1, Point(3, 2));
  logic->putNewCell(*board, *player2, Point(4, 2));
  logic->putNewCell(*board, *player1, Point(5, 3));

  Cell cell(Point(6, 4));
  EXPECT_TRUE(board->getCell(6, 4)->isEmpty());
  player2->makeMove(*board, *logic);
  EXPECT_FALSE(board->getCell(6, 4)->isEmpty());
  EXPECT_EQ(board->getPlayer(6, 4), player2);
}

// Works if AI find the correct maximum he can.
TEST_F(logicTest, AIfindsCorrentMaximum) {
  Computer *computer = new Computer('o');
  logic->putNewCell(*board, *player1, Point(3, 2));
  logic->putNewCell(*board, *computer, Point(4, 2));
  logic->putNewCell(*board, *player1, Point(5, 3));

  computer->makeMove(*board, *logic);
  logic->putNewCell(*board, *player1, Point(5, 4));
  int score = logic->aiFindMaxScore(*computer, *board, Point(6, 4));

  EXPECT_EQ(2, score);

  delete computer;
}

// Works if correct winner is returned.
TEST_F(logicTest, getWinnerWorks) {
  for (int i = 0; i < 15; i++) {
    player1->increaseScore();
    if (i % 2 == 0) {
      player2->increaseScore();
    }
  }
  EXPECT_EQ(player1, logic->getWinner(players));
}

// Works if enemy is detected correctly.
TEST_F(logicTest, isEnemyWorks) {
  EXPECT_TRUE(logic->isEnemy(player1, player2));
  EXPECT_FALSE(logic->isEnemy(player1, player1));
}