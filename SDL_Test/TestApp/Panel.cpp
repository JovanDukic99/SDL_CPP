#include "Panel.h"

Panel::Panel() {

}

Panel::Panel(SDL_Rect bounds, Color color) : HudBase(bounds, color) {

}

void Panel::init(SDL_Rect bounds, Color color) {
	setBounds(bounds);
	setColor(color);
}
