#include "cell.h"

using namespace std;

Cell::Cell(int x, int y) : point_(Point(x, y)) {
  player_ = NULL;
}

Cell::Cell(Point p) : point_(p) {
  player_ = NULL;
}

Cell::~Cell() {

}

Player *Cell::getPlayer() {
  return player_;
}

char Cell::getSymbol() const {
  if (player_->getSymbol()) {
    return player_->getSymbol();
  }
  return ' ';
}

bool Cell::isEmpty() {
  return player_ == NULL;
}

void Cell::fill(Player *p) {
  player_ = p;
}

int Cell::getX() const {
  return point_.getX();
}

int Cell::getY() const {
  return point_.getY();
}

void Cell::setX(int x) {
  point_.setX(x);
}

void Cell::setY(int y) {
  point_.setY(y);
}

bool Cell::operator==(const Cell &otherCell) const {
  return getX() == otherCell.getX() && getY() == otherCell.getY();
}

bool Cell::operator!=(const Cell &otherCell) const {
  return point_.getX() != otherCell.getX() || point_.getY() != otherCell.getY();
}

std::ostream &operator<<(std::ostream &out, Cell const &c) {
  return out << "(" << c.getX() + 1 << ", " << c.getY() + 1 << ")";
}
