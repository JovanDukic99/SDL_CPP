#pragma once
#include "Component.h"
#include "InputManager.h"
#include "Color.h"
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
class ColorPicker
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Component colorPanel;
	Component toggleRed;
	Component toggleGreen;
	Component toggleBlue;

	Color color;

	bool clickedRed;
	bool clickedGreen;
	bool clickedBlue;
	bool visible;
public:
	// constructors
	ColorPicker();
	~ColorPicker();

	// init
	void init();

	// update
	void update(InputManager inputManager);

	// setters
	void closeWindow();

	// getters
	bool isVisible() const;
private:
	// init
	void initWindow();
	void initComponents();

	// update
	void updateToggleButton(glm::ivec2 mouseCoords, Component* toggleButton);

	// setters
	void setVisible(bool visible);
	void reset();

	// draw
	void draw();
};

