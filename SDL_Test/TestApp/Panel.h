#pragma once
#include "HudBase.h"
#include <SDL/SDL.h>
class Panel : public HudBase
{
public:
	// constructor
	Panel();
	Panel(SDL_Rect bounds, Color color);

	// init
	void init(SDL_Rect bounds, Color color);
};

