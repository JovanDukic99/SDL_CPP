#include "Component.h"

// constructor
Component::Component(SDL_Rect bounds, Color color, SDL_Texture* texture, int ID) : ID(ID), bounds(bounds), color(color), texture(texture) {

}

Component::Component(const Component& other) {
	bounds = other.bounds;
	color = other.color;
	texture = other.texture;
	ID = other.ID;
}

// getters
int Component::getID() {
	return ID;
}

SDL_Rect Component::getBounds() {
	return bounds;
}

SDL_Texture* Component::getTexture() {
	return texture;
}

Color Component::getColor() {
	return color;
}

// setters
void Component::setColor(Color color) {
	this->color = color;
}

// operator overload
bool Component::operator==(const Component& other) {
	return ID == other.ID;
}
