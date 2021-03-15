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
	Panel colorButtonPanel;
	std::vector<Button> colorButtons;
	std::vector<Button> buttons;
public:
	// constructors
	MainPanel();

	// init
	void init();
	void initComponents();
	void initPanels();
	void initColorButtons();

	// update
	bool update(InputManager inputManager);

	// getters
	std::vector<HudBase> getComponents();
	Button* getSelectedButton();
};