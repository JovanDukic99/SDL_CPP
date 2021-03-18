#pragma once
#include "ImageLoader.h"
#include "Color.h"
#include <SDL/SDL_render.h>
#include <SDL_TTF/SDL_ttf.h>
#include <string>	
class Font
{
private:
	TTF_Font* font;
	
public:
	// constructors
	Font();
	Font(std::string fontPath, int size);

	// init
	void init(std::string fontPath, int size);

	// getters
	SDL_Texture* getFontTexture(std::string text, Color color, SDL_Renderer* renderer);
	SDL_Rect getTextBounds(std::string text, int x, int y);

	// setters
	void setFont(TTF_Font*& font);
private:
	void loadFont(std::string fontPath, int size);
};

