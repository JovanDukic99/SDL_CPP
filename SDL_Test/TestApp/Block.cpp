#include "Block.h"

Block::Block(SDL_Rect bounds, Color color) : bounds(bounds), color(color), erased(false) {

}

void Block::setErased(bool erased) {
	this->erased = erased;
}

SDL_Rect* Block::getBounds() {
	return &bounds;
}

Color Block::getColor() const {
	return color;
}

bool Block::isErased() const {
	return erased;
}
