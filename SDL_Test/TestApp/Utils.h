#pragma once
#include "Color.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <SDL_TTF/SDL_ttf.h>
#include <string>
#include <vector>
class Utils
{
public:
	static bool squareCollision(SDL_Rect r1, SDL_Rect r2);
	static bool areColliding(SDL_Rect r1, SDL_Rect r2);
	static bool isPointInsideBounds(glm::ivec2 mouseCoords, SDL_Rect bounds);
	static int calculateRGBValueFromPositon(int x, int A, int B, int C);
	static int calculatePositionFromRGBValue(int A, int B, int C, int D);
	static std::vector<SDL_Rect> getLinePath(glm::ivec2 p1, glm::ivec2 p2, int pathWidth, int pathHeight);
	static Color getButtonColor(int index);
private:
	static glm::fvec2 lerp(glm::fvec2 p1, glm::fvec2 p2, float t);
};

