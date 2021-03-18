#pragma once
#include "InputManager.h"
#include "Component.h"
#include "ColorPicker.h"
#include "Font.h"
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
#include <vector>
#include <string>

class MainPanel
{
private:
	std::vector<Component> panels;
	std::vector<Component> colorButtons;
	std::vector<Component> brushButtons;
	std::vector<Component> utilityButtons;
	int brushSize;
	Color selectedColor;
	SDL_Renderer* renderer;
	Font font;
public:
	// constructors
	MainPanel();

	// init
	void init();

	// update
	bool update(InputManager inputManager);
	bool openColorPicker(InputManager inputManager);

	// getters
	std::vector<Component> getPanels() const;
	std::vector<Component> getColorButtons() const;
	std::vector<Component> getBrushButtons() const;
	std::vector<Component> getUtilityButtons() const;
	int getBrushSize() const;
	Color getSelectedColor() const;

	// setters
	void setRenderer(SDL_Renderer* renderer);
	void setSelectedColor(Color selectedColor);
	void setFont(Font font);
private:
	// init
	void initComponents();
	void initPanels();
	void initButtons();

	// update
	bool updateColorButtons(InputManager inputManager);
	bool updateBrushButtons(InputManager inputManager);
};