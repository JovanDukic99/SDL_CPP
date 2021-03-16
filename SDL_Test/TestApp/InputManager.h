#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
class InputManager
{
private:
	std::unordered_map<unsigned int, bool> keyMap;
	glm::ivec2 mouseCoordinates;
	bool moving;
	int clickNumber;
	unsigned int windowID;
public:
	// setters
	void pressKey(unsigned int keyID);
	void releaseKey(unsigned int keyID);
	void setMouseCoordinates(int x, int y);
	void setMoving(bool moving);
	void setClickNumber(int clickNumber);
	void setWindowID(unsigned int windowID);

	// getters
	glm::ivec2 getMouseCoordinates() const;
	bool isKeyPressed(unsigned int keyID);
	bool isMoving() const;
	bool isDoubleClick() const;
	unsigned int getWindowID() const;
};

