#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../point.h"

using testing::Eq;

namespace {
class pointTest : public testing::Test {
 protected:
  Point *point1;
  Point *point2;
 public:
  pointTest() {
    point1 = new Point(3, 3);
    point2 = new Point(5, 7);
  }

  ~pointTest() {
    delete point1;
    delete point2;
  }
};
}

// Checks if comparing two points works.
TEST_F(pointTest, pointsEqualWorks) {
  EXPECT_NE(*point1, *point2);
  point1->setX(5);
  point1->setY(7);
  EXPECT_EQ(*point1, *point2);
}

// Checks if setting a new point works.
TEST_F(pointTest, pointSetWorks) {
  EXPECT_EQ(3, point1->getX());
  EXPECT_EQ(3, point1->getY());

  point1->setX(5);
  point1->setY(7);

  EXPECT_NE(point1->getX(), 3);
  EXPECT_NE(point1->getY(), 3);

  EXPECT_EQ(5, point1->getX());
  EXPECT_EQ(7, point1->getY());
}
