#include "logic.h"

Logic::~Logic() {}

vector<Point> Logic::getPlayerCells(Board &board, const Player &player) {
  // Check all the cells in the board and add to the player.
  vector<Point> playerCells;

  int x = board.getX();
  int y = board.getY();

  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      if (board.getPlayer(i, j) != NULL) {
        if (*board.getPlayer(i, j) == player) {
          playerCells.push_back(Point(i, j));
        }
      }
    }
  }

  return playerCells;
}

bool Logic::isOptionInList(const Point &newOption, vector<Point> options) {
  for (vector<Point>::iterator it = options.begin(); it != options.end();
       ++it) {
    if ((it->getX() == newOption.getX()) && (it->getY() == newOption.getY())) {
      return true;
    }
  }
  return false;
}

Player *Logic::findRival(const Player &currPlayer, const Board &board) {
  int x = board.getX();
  int y = board.getY();
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      if ((!board.getCell(i, j)->isEmpty())
          && (*board.getPlayer(i, j) != currPlayer)) {
        return board.getPlayer(i, j);
      }
    }
  }
  return NULL;
}

Player *Logic::getWinner(Player *players[]) {
  if (players[0]->compareScore(players[1]) == 1) {
    return players[0];
  }
  return players[1];
}

bool Logic::isEnemy(Player *player1, Player *player2) const {
  if (player2->getSymbol() == 0 || player2->getSymbol() == 0) {
    return false;
  }
  return player1 != player2;
}

bool Logic::isTie(Player &player1, Player &player2) {
  return player1.getScore() == player2.getScore();
}