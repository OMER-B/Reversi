#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../server/commandsManager.h"

using testing::Eq;

namespace {
class serverTest : public testing::Test {
 protected:
  CommandsManager *cm;

 public:
  cellTest() {
    cm = CommandsManager::getInstance();

  }

  ~cellTest() {
  }
};
}

// Checks for equal and unequal of cells
TEST_F(serverTest, commandManagerWorks
) {
}

}
TEST_F(serverTest, serpeateWorks
) {
}
