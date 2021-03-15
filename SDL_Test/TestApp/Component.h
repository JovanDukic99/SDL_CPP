#pragma once
#include "Color.h"
#include <SDL/SDL_rect.h>
#include <SDL/SDL_render.h>
class Component
{
private:
	int ID;
	SDL_Rect bounds;
	SDL_Texture* texture;
	Color color;
public:
	// constructors
	Component(SDL_Rect bounds, Color color, SDL_Texture* texture = nullptr, int ID = -1);
	Component(const Component& other);

	// getters
	int getID();
	SDL_Rect getBounds();
	SDL_Texture* getTexture();
	Color getColor();

	// setters
	void setColor(Color color);

	// operator overload
	bool operator==(const Component& other);
};

