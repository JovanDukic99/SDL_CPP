#include "InputManager.h"

void InputManager::pressKey(unsigned int keyID) {
	keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID) {
	keyMap[keyID] = false;
}

void InputManager::setMouseCoordinates(int x, int y) {
	mouseCoordinates = glm::ivec2(x, y);
}

glm::ivec2 InputManager::getMouseCoordinates() {
	return mouseCoordinates;
}

bool InputManager::isKeyPressed(unsigned int keyID) {
	auto iterator = keyMap.find(keyID);

	if (iterator != keyMap.end()) {
		return iterator->second;
	}

	return false;
}
