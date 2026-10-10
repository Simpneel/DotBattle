#include <raylib.h>

int main() {
	// Initialization
	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Dot Battle");
	SetTargetFPS(60);
	// Game loop
	while (!WindowShouldClose()) {
		// Update
		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Welcome to Dot Battle!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	// De-Initialization
	CloseWindow();
	return 0;
}