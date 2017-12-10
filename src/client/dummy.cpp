#include "dummy.h"
Dummy::Dummy(char symbol) : Player(symbol) {}

int Dummy::makeMove(Board &board, Logic &logic, Display &display) {
  if(enemyPoint_.getX() == -1) {
    cout << "Enemy could not make a move." << endl;
    return 1;

  } else if (enemyPoint_.getX() == 0) {
    cout << "Other player has ended the game." << endl;
    return 2;

  } else {
    logic.putNewCell(board, *this, enemyPoint_);
    display.printBoard(&board);
    cout << "The enemy placed '" << *board.getPlayer(enemyPoint_) << "' on "
         << enemyPoint_ << "." << endl;
    return 0;

  }
}

void Dummy::setEnemyPoint(const Point &point) {
  enemyPoint_ = point;
}
