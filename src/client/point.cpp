#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <tgmath.h>
#include "point.h"

using namespace std;

Point::Point(int x, int y) : x_(x), y_(y) {}

Point::~Point() {}

int Point::getX() const {
  return x_;
}

string Point::toString() {
  ostringstream ss;
  ss << x_ << " " << y_;
  string s = ss.str();
  return s;
}

int Point::getY() const {
  return y_;
}

void Point::setX(int x) {
  x_ = x;
}

void Point::setY(int y) {
  y_ = y;
}

Point Point::decrease() {
  return Point(x_-1, y_-1);
}

bool Point::operator==(const Point &point) const {
  return x_ == point.getX() && y_ == point.getY();
}

bool Point::operator!=(const Point &point) const {
  return x_ != point.getX() || y_ != point.getY();
}

Point::Point(char point[]) {
  x_ = 0;
  y_ = 0;
  int i = 0;
  while (point[i] != ' ') {
    x_ *= 10;
    x_ += (point[i] - 48);
    i++;
  }
  i++;
  while (point[i] != '\0') {
    y_ *= 10;
    y_ += (point[i] - 48);
    i++;
  }
}

std::ostream &operator<<(std::ostream &out, Point const &point) {
  return out << "(" << point.getX() + 1 << ", " << point.getY() + 1 << ")";
}