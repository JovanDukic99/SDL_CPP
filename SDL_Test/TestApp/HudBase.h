#pragma once
#include "Color.h"
#include <SDL/SDL.h>
class HudBase
{
private:
	Color color;
	SDL_Rect bounds;
public:
	// constructor
	HudBase();
	HudBase(SDL_Rect bounds, Color color);

	// setters
	void setColor(Color color);
	void setBounds(SDL_Rect bounds);

	// getters
	Color getColor();
	SDL_Rect* getBounds();
};

