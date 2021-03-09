#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
class InputManager
{
private:
	std::unordered_map<unsigned int, bool> keyMap;
	glm::ivec2 mouseCoordinates;
public:
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	void setMouseCoordinates(int x, int y);
	glm::ivec2 getMouseCoordinates();
	bool isKeyPressed(unsigned int keyID);
};

