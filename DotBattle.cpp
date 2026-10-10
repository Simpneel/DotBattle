#include "Tilemap.h"

int main() {
	const int screenWidth = 1080;
	const int screenHeight = 720;
	InitWindow(screenWidth, screenHeight, "Dot Battle");
	SetTargetFPS(60);


	// Game loop
	while (!WindowShouldClose()) {
		// Update
		// 
		// 
		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello World", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	// De-Initialization
	CloseWindow();
	return 0;
}