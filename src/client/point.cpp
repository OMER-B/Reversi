#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include "point.h"

using namespace std;

Point::Point(int x, int y) : x_(x), y_(y) {}

Point::~Point() {}

int Point::getX() const {
  return x_;
}

string Point::toString() {
  ostringstream ss;
  ss << x_ << ", " << y_;
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

bool Point::operator==(const Point &point) const {
  return x_ == point.getX() && y_ == point.getY();
}

bool Point::operator!=(const Point &point) const {
  return x_ != point.getX() || y_ != point.getY();
}

Point::Point(string point) {
  unsigned long pos = point.find_first_of(',');
  x_ = atoi(point.substr(0, pos).c_str());
  y_ = atoi(point.substr(pos + 2).c_str());
}

std::ostream &operator<<(std::ostream &out, Point const &point) {
  return out << "(" << point.getX() + 1 << ", " << point.getY() + 1 << ")";
}