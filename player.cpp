#include <exception>
#include "player.h"
#include "logic.h"

Player::Player(char symbol) {
  symbol_ = symbol;
  score_ = 0;
}

char Player::getSymbol() const {
  try {
    if (this) {
      return symbol_;
    }
  } catch (std::exception &) {
  }
  return ' ';
}

Player::~Player() {

}

int Player::getScore() const {
  return score_;
}

void Player::increaseScore() {
  score_++;
}

void Player::decreaseScore() {
  score_--;
}

bool Player::operator==(const Player &player) const {
  return symbol_ == player.getSymbol();
}

bool Player::operator!=(const Player &player) const {
  return symbol_ != player.getSymbol();
}

int Player::compareScore(Player *player) const {
  if (score_ > player->getScore()) {
    return 1;
  }
  if (score_ < player->getScore()) {
    return -1;
  }
  return 0;
}

void Player::setScore(int score) {
  score_ = score;
}

std::ostream &operator<<(std::ostream &out, Player const &player) {
  return out << player.getSymbol();
}
