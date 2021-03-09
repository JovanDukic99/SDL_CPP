#include "Player.h"
#include "Config.h"

Player::Player(int startX, int startY, int width, int height) : position(startX, startY), dimensions(width, height), bounds(new SDL_Rect) {
	init();
}

void Player::init() {
	updateBounds();
}

void Player::update(InputManager inputManager) {
	if (inputManager.isKeyPressed(SDLK_w)) {
		position.y -= PLAYER_SPEEX_Y;
	}

	if (inputManager.isKeyPressed(SDLK_s)) {
		position.y += PLAYER_SPEEX_Y;
	}

	if (inputManager.isKeyPressed(SDLK_a)) {
		position.x -= PLAYER_SPEEX_X;
	}

	if (inputManager.isKeyPressed(SDLK_d)) {
		position.x += PLAYER_SPEEX_X;
	}

	updateBounds();
}

void Player::updateBounds() {
	// set position
	bounds->x = position.x;
	bounds->y = position.y;

	// set dimensions
	bounds->w = dimensions.x;
	bounds->h = dimensions.y;
}

// setters
SDL_Rect* Player::getBounds() {
	return bounds;
}