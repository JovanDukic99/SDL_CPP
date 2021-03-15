#pragma once
#include "Color.h"
#include <SDL/SDL.h>
class Block
{
private:
	SDL_Rect bounds;
	Color color;
	bool erased;
public:
	// constructor
	Block(SDL_Rect bounds, Color color);

	// setters
	void setErased(bool erased);

	// getters
	SDL_Rect* getBounds();
	Color getColor() const;
	bool isErased() const;
};

