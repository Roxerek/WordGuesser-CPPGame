#pragma once

#include <SDL_render.h>

struct TextItem {
	
	bool render;
	SDL_Texture* texture;
	SDL_Rect rectangle;
	int w;
	int h;
	char letter;

};