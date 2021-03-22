#pragma once
#include "ImageLoader.h"
#include "Color.h"
#include <SDL/SDL_render.h>
#include <SDL_TTF/SDL_ttf.h>
#include <glm/glm.hpp>
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
	void obtainTextData(std::string text, Color color, SDL_Renderer* renderer, SDL_Texture** texture, SDL_Rect* bounds, glm::ivec2 position);

	// setters
	void setFont(TTF_Font*& font);
private:
	void loadFont(std::string fontPath, int size);
};

