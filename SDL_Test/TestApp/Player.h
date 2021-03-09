#pragma once
#include "InputManager.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>

class Player
{
private:
	glm::ivec2 position;
	glm::ivec2 dimensions;
	SDL_Rect* bounds;
public:
	// constructor
	Player(int startX, int startY, int width, int height);

	// update
	void update(InputManager inputManager);

	// getters
	SDL_Rect* getBounds();
private:
	// init
	void init();

	// update
	void updateBounds();
};

