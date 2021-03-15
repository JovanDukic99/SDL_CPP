#pragma once
#include "InputManager.h"
#include "Button.h"
#include "Panel.h"
#include <SDL/SDL.h>
#include <vector>

class MainPanel
{
private:
	Panel panel;
	std::vector<Button> colorButtons;
	std::vector<Button> buttons;
public:
	// constructors
	MainPanel();

	// init
	void init();
	void initComponents();

	// update
	bool update(InputManager inputManager);

	// getters
	std::vector<HudBase> getComponents();
	Button* getSelectedButton();
};