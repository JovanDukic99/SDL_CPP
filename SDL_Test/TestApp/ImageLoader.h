#pragma once
#include <SDL/SDL_surface.h>
#include <SDL/SDL_render.h>
#include <string>
class ImageLoader
{
public:
	static SDL_Texture* loadTexture(std::string filePath, SDL_Renderer* renderer);
};

