#pragma once
#include "Color.h"
#include <SDL/SDL_surface.h>
#include <SDL/SDL_render.h>
#include <SDL_TTF/SDL_ttf.h>
#include <unordered_map>
#include <string>
class ImageLoader
{
private:
	static std::unordered_map<std::string, SDL_Surface*> surfaceMap;
private:
	ImageLoader();
	~ImageLoader();
public:
	static SDL_Texture* loadTexture(std::string filePath, SDL_Renderer* renderer);
	static SDL_Surface* loadSurface(std::string filePath);
	static SDL_Surface* loadCursor(std::string filePath);
	static SDL_Texture* getFontTexture(std::string text, TTF_Font* font, Color color, SDL_Renderer* renderer);
private:
	static SDL_Surface* findSurface(std::string filePath);
};

