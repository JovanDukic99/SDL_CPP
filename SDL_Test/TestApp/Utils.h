#pragma once
#include "Color.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>
class Utils
{
public:
	static bool squareCollision(SDL_Rect r1, SDL_Rect r2);
	static bool areColliding(SDL_Rect r1, SDL_Rect r2);
	static bool isPointInsideBounds(glm::ivec2 mouseCoords, SDL_Rect bounds);
	static int calculateRGBValueFromPositon(int x, int A, int B, int C);
	static int calculatePositionFromRGBValue(int A, int B, int C, int D);
	static Color getButtonColor(int index);
};

