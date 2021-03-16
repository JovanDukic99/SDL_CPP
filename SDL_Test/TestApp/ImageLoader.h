#pragma once
#include <SDL/SDL_surface.h>
#include <SDL/SDL_render.h>
#include <SDL_TTF/SDL_ttf.h>
#include <string>
class ImageLoader
{
public:
	static SDL_Texture* loadTexture(std::string filePath, SDL_Renderer* renderer);
	static SDL_Texture* getTexture(std::string text, TTF_Font* font, SDL_Renderer* renderer);
};

