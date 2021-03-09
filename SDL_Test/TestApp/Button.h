#pragma once
#include "HudBase.h"
#include <SDL/SDL.h>
class Button : public HudBase
{
private:
	static int nextID;
	int ID;
public:
	// constructor
	Button();
	Button(SDL_Rect bounds, Color color);

	// init
	void init(SDL_Rect bounds, Color color);

	// getters
	int getID();
};

