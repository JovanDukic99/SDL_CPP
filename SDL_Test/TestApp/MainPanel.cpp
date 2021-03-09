#include "MainPanel.h"
#include "Config.h"

MainPanel::MainPanel() {
	init();
}

void MainPanel::init() {
	initComponents();
}

void MainPanel::initComponents() {
	SDL_Rect panelBounds;

	panelBounds.x = PANEL_X;
	panelBounds.y = PANEL_Y;
	panelBounds.w = PANEL_WIDTH;
	panelBounds.h = PANEL_HEIGHT;

	panel.init(panelBounds, BLUE);

	buttons.reserve(BUTTON_NUMBER);

	for (size_t i = 0; i < BUTTON_NUMBER; i++) {
		SDL_Rect bounds;

		bounds.w = PANEL_BUTTON_WIDTH;
		bounds.h = PANEL_BUTTON_HEIGHT;

		bounds.x = BUTTON_START_X + i * BUTTON_SAPWN_DIFF_X;
		bounds.y = BUTTON_START_Y;

		buttons.emplace_back(bounds, YELLOW);
	}

	buttons[0].setColor(RED);
}

void MainPanel::update(InputManager inputManager) {
	glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

	// if there already selected button
	Button* selectedButton = nullptr;

	for (size_t i = 0; i < buttons.size(); i++) {
		if (buttons[i].getColor() == RED) {
			selectedButton = &buttons[i];
		}
	}

	// if change has occured
	bool flag = false;

	for (size_t i = 0; i < buttons.size(); i++) {
		Button button = buttons[i];
		SDL_Rect bounds = *button.getBounds();

		if (mouseCoords.x >= bounds.x && mouseCoords.x <= bounds.x + bounds.w) {
			if (mouseCoords.y >= bounds.y && mouseCoords.y <= bounds.y + bounds.h) {
				// if we have clicked already selected button just return
				if (selectedButton == &buttons[i]) {
					return;
				}
				else {
					buttons[i].setColor(RED);
					flag = true;
					break;
				}
			}
		}	
	}

	// if there is already selected button and if change has occured
	if (selectedButton != nullptr && flag) {
		selectedButton->setColor(YELLOW);
	}
}

// getters
std::vector<HudBase> MainPanel::getComponents() {
	std::vector<HudBase> components;

	components.reserve(buttons.size() + 1);

	components.push_back(panel);
	
	components.insert(components.begin() + 1, buttons.begin(), buttons.end());

	return components;
}

Button* MainPanel::getSelectedButton() {
	for (size_t i = 0; i < buttons.size(); i++) {
		if (buttons[i].getColor() == RED) {
			return &buttons[i];
		}
	}
	return nullptr;
}
