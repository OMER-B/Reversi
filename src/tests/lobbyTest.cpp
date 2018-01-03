#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/lobbyTest.h"
#include "../server/Lobby.h"
#include "lib/googletest-master/googletest/include/gtest/gtest.h"
#include "lib/googletest-master/googletest/include/gtest/internal/gtest-internal.h"

using testing::Eq;

namespace {


  //constructor: create a list of rooms
  // test: create a room
  // test: add a new room
  // test: remove a room

  class lobbyTest : public testing::Test {
  protected:
    Lobby *lobby_;

  public:
    lobbyTest() {
      //constructor:
      lobby_ = new Lobby();
    }

    ~remoteTest() {
      delete lobby_;
    }
  };
}

TEST_F(lobbyTest, addNewRoom) {
  EXPECT_FALSE(lobby_->contains("room1"));
Room *room1 = lobby_->createRoom("room1");
EXPECT_TRUE(lobby_->contains("room1"));
};

TEST_F(lobbyTest, deleteRoom) {
  Room *room2 = lobby_->createRoom("room2");
  EXPECT_TRUE(lobby_->contains("room2"));
  lobby_->removeRoom("room2");
  EXPECT_FALSE(lobby_->contains("room2"));
}

TEST_F(lobbyTest, checkListOfRooms) {
  Room * room3 = lobby_->createRoom("room3");
  Room * room4 = lobby_->createRoom("room4");
  vector<string> list = lobby_->getListOfRooms();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.at(0), "room3");
  EXPECT_EQ(list.at(1), "room4");
};
