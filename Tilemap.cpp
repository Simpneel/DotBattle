#include "Tilemap.h"
#include <stdexcept>
#include <cmath>

Tilemap::Tilemap(int tileWidth, int tileHeight, float scale)
    : tileset{}, tileWidth(tileWidth), tileHeight(tileHeight), tilesPerRow(0),
      map(), mapWidth(0), mapHeight(0), scale(scale), loaded(false) {}

Tilemap::~Tilemap() {
    unload();
}

bool Tilemap::load(const std::string& path) {
    unload();
    tileset = LoadTexture(path.c_str());
    if (tileset.id == 0) {
        loaded = false;
        return false;
    }
    if (tileWidth <= 0 || tileHeight <= 0) {
        UnloadTexture(tileset);
        loaded = false;
        return false;
    }
    tilesPerRow = tileset.width / tileWidth;
    if (tilesPerRow <= 0) {
        UnloadTexture(tileset);
        loaded = false;
        return false;
    }
    loaded = true;
    return true;
}

void Tilemap::unload() {
    if (loaded) UnloadTexture(tileset);
    loaded = false;
    map.clear();
    mapWidth = mapHeight = 0;
}

void Tilemap::setMap(const std::vector<int>& mapData, int width, int height) {
    if (width <= 0 || height <= 0 || static_cast<int>(mapData.size()) != width * height)
        throw std::invalid_argument("Map dimensions must match vector size");
    map = mapData;
    mapWidth = width;
    mapHeight = height;
}

int Tilemap::getTileAt(int tx, int ty) const {
    if (tx < 0 || ty < 0 || tx >= mapWidth || ty >= mapHeight) return -1;
    return map[ty * mapWidth + tx];
}

void Tilemap::setTileAt(int tx, int ty, int tileIndex) {
    if (tx < 0 || ty < 0 || tx >= mapWidth || ty >= mapHeight) return;
    map[ty * mapWidth + tx] = tileIndex;
}

void Tilemap::worldToTile(float worldX, float worldY, int& outTx, int& outTy) const {
    const float dstW = tileWidth * scale;
    const float dstH = tileHeight * scale;
    outTx = static_cast<int>(std::floor(worldX / dstW));
    outTy = static_cast<int>(std::floor(worldY / dstH));
}

void Tilemap::draw(const Camera2D& camera, int screenWidth, int screenHeight) const {
    if (!loaded || map.empty()) return;

    const float dstW = tileWidth * scale;
    const float dstH = tileHeight * scale;

    // Compute visible world rectangle from the camera and screen size
    const float viewLeft = camera.target.x - camera.offset.x / camera.zoom;
    const float viewTop = camera.target.y - camera.offset.y / camera.zoom;
    const float viewRight = viewLeft + screenWidth / camera.zoom;
    const float viewBottom = viewTop + screenHeight / camera.zoom;

    // Convert to tile indices and clamp to map bounds
    int minTileX = static_cast<int>(std::floor(viewLeft / dstW));
    int minTileY = static_cast<int>(std::floor(viewTop / dstH));
    int maxTileX = static_cast<int>(std::floor((viewRight) / dstW));
    int maxTileY = static_cast<int>(std::floor((viewBottom) / dstH));

    if (minTileX < 0) minTileX = 0;
    if (minTileY < 0) minTileY = 0;
    if (maxTileX >= mapWidth) maxTileX = mapWidth - 1;
    if (maxTileY >= mapHeight) maxTileY = mapHeight - 1;

    for (int y = minTileY; y <= maxTileY; ++y) {
        for (int x = minTileX; x <= maxTileX; ++x) {
            int idx = map[y * mapWidth + x];
            if (idx < 0) continue;
            int sx = (idx % tilesPerRow) * tileWidth;
            int sy = (idx / tilesPerRow) * tileHeight;
            Rectangle src{ (float)sx, (float)sy, (float)tileWidth, (float)tileHeight };

            // World position of the tile
            const float wx = x * dstW;
            const float wy = y * dstH;
            Rectangle dst{ wx, wy, dstW, dstH };

            DrawTexturePro(tileset, src, dst, {0.0f, 0.0f}, 0.0f, WHITE);
        }
    }
}
