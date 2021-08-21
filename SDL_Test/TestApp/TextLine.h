#pragma once
#include <string>
#include <glm/glm.hpp>
#include <SDL/SDL_render.h>
#include <SDL/SDL.h>
#include "Font.h"
#include "InputManager.h"
class TextLine
{
private:
	std::string text;
	Uint32 deleteTimer;
	Uint32 cursorTimer;
	Font* font;
	InputManager* inputManager;
	SDL_Renderer* renderer;
	glm::ivec2 cursorPosition;
	glm::ivec2 textPosition;
	int size;
public:
	TextLine(glm::ivec2 textPosition, int size, SDL_Renderer* renderer, Font* font);
	~TextLine();
	void draw();
	void update(Uint32 deltaTime);
	int getSize();
private:
	void init();
	void reset();
	void updateText(Uint32 deltaTime);
	void updateCursor();
	void drawText();
	void drawCursor();
};

