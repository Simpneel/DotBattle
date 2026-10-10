#pragma once
#include "RaylibWrapper.h"

#define TILE_SIZE 32
#

class Tilemap {

private:
	Image tile_brick;
	Image tile_grass;
	Image tile_water;
	Image tile_stone;
	Image tile_box;
	Image tile_wall;


public:

	Tilemap();
	~Tilemap();

	void LoadTilemap();

};
