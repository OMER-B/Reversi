#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/computer.h"
#include "../client/human.h"

using testing::Eq;

namespace {
class playerTest : public testing::Test {
 public:
  Player *player;
  playerTest() {
    player = new Human('x');
  }

  ~playerTest() {
    delete player;
  }
};
}

/* Tests if the score updates. */
TEST_F(playerTest, worksIfScoreUpdates) {
  EXPECT_EQ(player->getScore(), 0);
  player->increaseScore();
  EXPECT_EQ(player->getScore(), 1);
  player->decreaseScore();
  EXPECT_EQ(player->getScore(), 0);
}

// Tests if the correct symbol is returned.
TEST_F(playerTest, worksIfSymbolReturned) {
  EXPECT_EQ(player->getSymbol(), 'x');
}

// Tests if two players are the same or different works.
TEST_F(playerTest, WorksIfEqualWorks) {
  EXPECT_TRUE(player == player);
  EXPECT_FALSE(player != player);

  Player *player2 = new Computer('x');

  EXPECT_TRUE(player != player2);
  EXPECT_FALSE(player == player2);

  delete player2;
  player2 = new Computer('x');

  EXPECT_FALSE(player == player2);
  EXPECT_TRUE(player != player2);

  delete player2;
  player2 = new Human('o');

  EXPECT_FALSE(player == player2);
  EXPECT_TRUE(player != player2);

  delete player2;
}
