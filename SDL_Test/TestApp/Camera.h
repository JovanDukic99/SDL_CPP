#pragma once
#include <glm/glm.hpp>
class Camera
{
private:
	glm::vec2 position;
public:
	// constructor
	Camera(int startX, int startY);

	// update
	void update(int x, int y);
};

