#pragma once
#include "raylib.h"

class PlayerController {
private:
    Vector2 position;
    float movespeed;   // pixels per second
    int size;
    Color color;

public:
    PlayerController();
    PlayerController(float x, float y, float speed = 200.0f, int size = 16);

    // Updated: pass inputDir so we avoid calling IsKeyDown per-entity
    void update(const Vector2& inputDir, float deltaTime);

    // Render player
    void draw() const;

    void setPosition(float x, float y);
    Vector2 getPosition() const;
};