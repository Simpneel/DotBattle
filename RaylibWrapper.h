#include <raylib.h>

class RaylibWrapper {

private:
	//variables

	//functions

public:
	//variables

	//functions
	Image TileMapSplicer(Image tileMapImg, int x, int y);
	Texture2D TextureLoad(Image img) { return LoadTextureFromImage(img); }
	void TextureUnload(Texture2D texture) { UnloadTexture(texture); }

	

};