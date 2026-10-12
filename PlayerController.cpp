#include "PlayerController.h"
#include <cmath>

PlayerController::PlayerController()
    : position{ 0.0f, 0.0f }, movespeed(200.0f), size(16), color(BLUE) {}

PlayerController::PlayerController(float x, float y, float movespeedIn, int sizeIn)
    : position{ x, y }, movespeed(movespeedIn), size(sizeIn), color(BLUE) {}

// Use inputDir already computed by the app; avoid sqrt by simple diagonal scaling
void PlayerController::update(const Vector2& inputDir, float deltaTime) {
    Vector2 dir = inputDir;
    if (dir.x == 0.0f && dir.y == 0.0f) return;

    // cheap diagonal normalization: if moving diagonally, scale by 1/sqrt(2)
    if (dir.x != 0.0f && dir.y != 0.0f) {
        const float diag = 0.70710678f;
        dir.x *= diag;
        dir.y *= diag;
    }

    position.x += dir.x * movespeed * deltaTime;
    position.y += dir.y * movespeed * deltaTime;
}

void PlayerController::draw() const {
    // Draw rectangle centered on position
    DrawRectangleV({ position.x - size * 0.5f, position.y - size * 0.5f }, { (float)size, (float)size }, color);
}

void PlayerController::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

Vector2 PlayerController::getPosition() const {
    return position;
}

