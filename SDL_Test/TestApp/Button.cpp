#include "Button.h"

int Button::nextID = 0;

Button::Button() : ID(nextID++) {

}

Button::Button(SDL_Rect bounds, Color color) : HudBase(bounds, color), ID(nextID++) {

}

void Button::init(SDL_Rect bounds, Color color) {
	HudBase::setBounds(bounds);
	HudBase::setColor(color);
}

int Button::getID() {
	return ID;
}
