#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/board.h"
#include "../client/regLogic.h"
#include "../client/client.h"


using testing::Eq;

namespace {
  class remoteTest : public testing::Test {
  protected:
    Board *board;
    Logic *logic;
    Client *client;
    Dummy *dummy;
    Player *players[2];

  public:
    remoteTest() {
      players[0] = new Client("settings");
      players[1] = client->getDummy();
      logic = new RegLogic();
      board = new Board(8, 8, players);
    }

    ~remoteTest() {
      delete board;
      delete logic;
      delete[] players;
    }
  };
}

