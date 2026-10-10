#pragma once
#include <vector>
#include <string>
#include "raylib.h"

class Tilemap {
private:
    Texture2D tileset;
    int tileWidth;
    int tileHeight;
    int tilesPerRow;
    std::vector<int> map;
    int mapWidth;
    int mapHeight;
    float scale;
    bool loaded;

public:
    Tilemap(int tileWidth = 8, int tileHeight = 8, float scale = 4.0f);
    ~Tilemap();

    bool load(const std::string& path);
    void unload();

    // mapData must be size width * height
    void setMap(const std::vector<int>& mapData, int width, int height);

    // Draw only tiles visible through the provided camera and screen size (view culling)
    void draw(const Camera2D& camera, int screenWidth, int screenHeight) const;

    int getTileDrawSize() const { return static_cast<int>(tileWidth * scale); }
    bool isLoaded() const { return loaded; }
};