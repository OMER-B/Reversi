#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../client/cell.h"

using testing::Eq;

namespace {
class cellTest : public testing::Test {
 protected:
  Cell *cell1;
  Cell *cell2;

 public:
  cellTest() {
    cell1 = new Cell(3, 3);
    cell2 = new Cell(5, 7);

  }

  ~cellTest() {
    delete cell1;
    delete cell2;
  }
};
}

// Checks for equal and unequal of cells
TEST_F(cellTest, cellsEqualWorks) {
  EXPECT_NE(*cell1, *cell2);
  cell1->setX(5);
  cell1->setY(7);
  EXPECT_EQ(*cell1, *cell2);
}

// Checks if new points are set for cell
TEST_F(cellTest, cellSetWorks) {
  EXPECT_EQ(3, cell1->getX());
  EXPECT_EQ(3, cell1->getY());

  cell1->setX(5);
  cell1->setY(7);

  EXPECT_NE(cell1->getX(), 3);
  EXPECT_NE(cell1->getY(), 3);

  EXPECT_EQ(5, cell1->getX());
  EXPECT_EQ(7, cell1->getY());
}
