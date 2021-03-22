#pragma once
#include "Font.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
#include <string>
class TextArea
{
private:
	std::string text;
	glm::ivec2 position;
	Font font;
	SDL_Renderer* renderer;
public:
	TextArea(std::string text, glm::ivec2 position, Font font, SDL_Renderer* renderer);

	// draw
	void draw();
};

