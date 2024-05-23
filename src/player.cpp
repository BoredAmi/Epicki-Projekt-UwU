#include "player.h"
Player::Player(float startX, float startY, float moveSpeed) : position(startX, startY), speed(moveSpeed) {}

void Player::move(float dx, float dy) {
    position.x += dx * speed;
    position.y += dy * speed;
}