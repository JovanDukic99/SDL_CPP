#pragma once
#include "Color.h"
#include <SDL/SDL.h>
class Utils
{
public:
	static bool squareCollision(SDL_Rect r1, SDL_Rect r2);
	static bool areColliding(SDL_Rect r1, SDL_Rect r2);
	static Color getButtonColor(int index);
};

