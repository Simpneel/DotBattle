#include "Tilemap.h"
#include "PlayerController.h"
#include <vector>
#include <string>

int main() {
    const int screenWidth = 1080;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Dot Battle - Good Luck");
    SetTargetFPS(60);

    // Tilemap: tiles are 8x8 in the provided tileset; scale up for visibility
    Tilemap tilemap(8, 8, 4.0f);
    const std::string tilesetPath = "ref/tileImage.png"; // use relative path; set working dir to project or copy ref to output
    if (!tilemap.load(tilesetPath)) {
        // If loading fails, app will still run but tiles won't draw
    }

    int tileSizePx = tilemap.getTileDrawSize();
    int mapW = std::max(1, screenWidth / tileSizePx);
    int mapH = std::max(1, screenHeight / tileSizePx);

    // Generate a simple patterned map (0..63)
    std::vector<int> map(mapW * mapH);
    for (int y = 0; y < mapH; ++y) {
        for (int x = 0; x < mapW; ++x) {
            map[y * mapW + x] = (x + y * 3) % 64;
        }
    }
    tilemap.setMap(map, mapW, mapH);

    // Player in the center (position is center of player)
    PlayerController player((float)screenWidth / 2.0f, (float)screenHeight / 2.0f, 220.0f, 16);

    // Camera that follows the player
    Camera2D camera;
    camera.offset = { screenWidth * 0.5f, screenHeight * 0.5f }; // center of screen
    camera.target = player.getPosition();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    bool editorOpen = false;

    // Game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- Aggregate input once per frame ---
        Vector2 inputDir{ 0.0f, 0.0f };
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    inputDir.y -= 1.0f;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  inputDir.y += 1.0f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  inputDir.x -= 1.0f;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) inputDir.x += 1.0f;

        // Toggle editor window overlay on '+' (numpad plus or Shift+=)
        if (IsKeyPressed(KEY_KP_ADD) || (IsKeyPressed(KEY_EQUAL) && IsKeyDown(KEY_LEFT_SHIFT))) {
            editorOpen = !editorOpen;
        }

        // Example: update 100 player-like entities (here only one variable shown)
        // For a real ECS, iterate component arrays and call update per entity
        player.update(inputDir, dt);
        // Update camera target to follow player, but clamp so camera doesn't show beyond map edges
        Vector2 target = player.getPosition();
        camera.target = target;

        // Map size in world pixels
        const float worldW = static_cast<float>(mapW * tileSizePx);
        const float worldH = static_cast<float>(mapH * tileSizePx);

        // Half-size of the view in world coordinates (accounting for zoom)
        const float halfViewW = camera.offset.x / camera.zoom;
        const float halfViewH = camera.offset.y / camera.zoom;

        // Clamp X
        if (worldW <= halfViewW * 2.0f) {
            camera.target.x = worldW * 0.5f; // center if world smaller than view
        } else {
            if (camera.target.x < halfViewW) camera.target.x = halfViewW;
            if (camera.target.x > worldW - halfViewW) camera.target.x = worldW - halfViewW;
        }

        // Clamp Y
        if (worldH <= halfViewH * 2.0f) {
            camera.target.y = worldH * 0.5f;
        } else {
            if (camera.target.y < halfViewH) camera.target.y = halfViewH;
            if (camera.target.y > worldH - halfViewH) camera.target.y = worldH - halfViewH;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
            tilemap.draw(camera, screenWidth, screenHeight);
            player.draw();
            // ... draw other entities (use same inputDir for all player-controlled)
        EndMode2D();

        // Editor overlay (drawn in screen-space)
        if (editorOpen) {
            const int w = 400, h = 240;
            const int x = (screenWidth - w) / 2;
            const int y = (screenHeight - h) / 2;
            DrawRectangle(x, y, w, h, Fade(DARKGRAY, 0.9f));
            DrawRectangleLines(x, y, w, h, BLACK);
            DrawText("Map Editor (overlay) - Press + to close", x + 12, y + 12, 16, RAYWHITE);
            DrawText("Editor implementation not included.", x + 12, y + 40, 14, LIGHTGRAY);
        }

        DrawText("Dot Battle - WASD to move - Press + to toggle editor", 10, 10, 16, LIGHTGRAY);

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}