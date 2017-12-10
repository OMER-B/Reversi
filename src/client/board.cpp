#include "board.h"

using namespace std;

Board::Board(int x, int y, Player *players[]) {
  x_ = x;
  y_ = y;
  counter_ = 0;
  cells_ = new Cell *[x_];
  for (int i = 0; i < x_; ++i) {
    cells_[i] = new Cell[y_];
  }
  Board::initialize(players);
}

Board::Board(const Board &board) {
  x_ = board.getX();
  y_ = board.getY();
  cells_ = new Cell *[x_];
  for (int i = 0; i < x_; ++i) {
    cells_[i] = new Cell[y_];
  }
  for (int i = 0; i < x_; i++) {
    for (int j = 0; j < y_; j++) {
      cells_[i][j].setX(i);
      cells_[i][j].setY(j);
      if (board.getPlayer(i, j) != NULL) {
        cells_[i][j].fill(board.getPlayer(i, j));
      }
    }
  }
}

Board::~Board() {
  for (int i = 0; i < x_; ++i)
    delete[] cells_[i];
  delete[] cells_;
}

void Board::initialize(Player *const players[]) {
  for (int i = 0; i < x_; i++) {
    for (int j = 0; j < y_; j++) {
      cells_[i][j].setX(i);
      cells_[i][j].setY(j);
    }
  }

  cells_[(x_ / 2) - 1][(y_ / 2) - 1].fill(players[1]);
  cells_[(x_ / 2) - 1][(y_ / 2)].fill(players[0]);
  cells_[(x_ / 2)][(y_ / 2) - 1].fill(players[0]);
  cells_[(x_ / 2)][(y_ / 2)].fill(players[1]);
  for (int i = 0; i < 2; i++) {
    for (int i = 0; i < 2; i++) {
      players[i]->increaseScore();
    }
  }
  counter_ = 4;
}

Cell *Board::getCell(int i, int j) const {
  return &cells_[i][j];
}

Cell *Board::getCell(Point point) const {
  return &cells_[point.getX()][point.getY()];
}

bool Board::inBoundaries(int x, int y) const {
  return (x >= 0 && y >= 0 && x < x_ && y < y_);
}

bool Board::inBoundaries(Point point) const {
  return (point.getX() >= 0 && point.getY() >= 0 && point.getX() < x_
      && point.getY() < y_);
}

int Board::getY() const {
  return y_;
}

int Board::getX() const {
  return x_;
}

void Board::fillCell(Point point, Player *player) {
  if (cells_[point.getX()][point.getY()].isEmpty()) {
    counter_++;
  }
  cells_[point.getX()][point.getY()].fill(player);
}
Player *Board::getPlayer(int i, int j) const {
  return cells_[i][j].getPlayer();
}

Player *Board::getPlayer(Cell cell) const {
  return cells_[cell.getX()][cell.getY()].getPlayer();
}

Player *Board::getPlayer(Point point) const {
  return cells_[point.getX()][point.getY()].getPlayer();
}

bool Board::isFull() const {
  return counter_ == x_ * y_;
}