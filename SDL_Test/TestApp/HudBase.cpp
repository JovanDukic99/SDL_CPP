#include "HudBase.h"

HudBase::HudBase() : bounds(), color(WHITE) {

}

HudBase::HudBase(SDL_Rect bounds, Color color) : bounds(bounds), color(color){

}

// setters
void HudBase::setColor(Color color) {
	this->color = color;
}

void HudBase::setBounds(SDL_Rect bounds) {
	this->bounds = bounds;
}

// getters
Color HudBase::getColor() {
	return color;
}

SDL_Rect* HudBase::getBounds() {
	return &bounds;
}
