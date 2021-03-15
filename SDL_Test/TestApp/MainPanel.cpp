#include "MainPanel.h"
#include "Config.h"
#include "Utils.h"
#include "ImageLoader.h"

MainPanel::MainPanel() : brushSize(1) {
	
}

void MainPanel::init() {
	initComponents();
}

void MainPanel::initComponents() {
	initPanels();
	initButtons();
}

void MainPanel::initPanels() {
	panels.reserve(2);
	// ================= <Main Panel> ================= //
	SDL_Rect mainPanelBounds;

	mainPanelBounds.w = MAIN_PANEL_WIDTH;
	mainPanelBounds.h = MAIN_PANEL_HEIGHT;

	mainPanelBounds.x = MAIN_PANEL_START_X;
	mainPanelBounds.y = MAIN_PANEL_START_Y;

	panels.emplace_back(mainPanelBounds, SILVER);

	// ================= <Color Panel> ================= //
	SDL_Rect colorPanelBounds;

	colorPanelBounds.w = COLOR_PANEL_WIDTH;
	colorPanelBounds.h = COLOR_PANEL_HEIGHT;

	colorPanelBounds.x = COLOR_PANEL_START_X;
	colorPanelBounds.y = COLOR_PANEL_START_Y;

	panels.emplace_back(colorPanelBounds, GRAY);
}

void MainPanel::initButtons() {
	// ================= <Color Buttons> ================= //
	colorButtons.reserve(COLOR_BUTTON_NUMBER);

	for (size_t i = 0; i < 2; i++) {
		for (size_t j = 0; j < COLOR_BUTTON_NUMBER / 2; j++) {
			SDL_Rect bounds;

			bounds.w = COLOR_BUTTON_WIDTH;
			bounds.h = COLOR_BUTTON_HEIGHT;

			bounds.x = COLOR_BUTTON_START_X + j * COLOR_BUTTON_OFFSET;
			bounds.y = COLOR_BUTTON_START_Y + i * COLOR_BUTTON_OFFSET;

			colorButtons.emplace_back(bounds, Utils::getButtonColor(i * COLOR_BUTTON_NUMBER / 2 + j));
		}
	}

	// ================= <Brush Buttons> ================= //
	brushButtons.reserve(2);
	for (size_t i = 0; i < 2; i++) {
		SDL_Texture* texutre = nullptr;
		if (i == 0) {
			texutre = ImageLoader::loadTexture(PLUS_BUTTON_PATH, renderer);
		}
		else {
			texutre = ImageLoader::loadTexture(MINUS_BUTTON_PATH, renderer);
		}
		
		SDL_Rect bounds;

		bounds.w = PANEL_BUTTON_WIDTH;
		bounds.h = PANEL_BUTTON_HEIGHT;

		bounds.x = BUTTON_START_X + i * BUTTON_SAPWN_DIFF_X;
		bounds.y = BUTTON_START_Y;

		brushButtons.emplace_back(bounds, BLACK, texutre, i);
	}
}

bool MainPanel::update(InputManager inputManager) {
	return updateColorButtons(inputManager) || updateBrushButtons(inputManager);
}

bool MainPanel::updateColorButtons(InputManager inputManager) {
	glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

	for (size_t i = 0; i < colorButtons.size(); i++) {
		SDL_Rect bounds = colorButtons[i].getBounds();

		if (mouseCoords.x >= bounds.x && mouseCoords.x <= bounds.x + bounds.w) {
			if (mouseCoords.y >= bounds.y && mouseCoords.y <= bounds.y + bounds.h) {
				color = colorButtons[i].getColor();
				return true;
			}
		}
	}

	return false;
}

bool MainPanel::updateBrushButtons(InputManager inputManager) {
	glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

	for (size_t i = 0; i < brushButtons.size(); i++) {
		SDL_Rect bounds = brushButtons[i].getBounds();

		if (mouseCoords.x >= bounds.x && mouseCoords.x <= bounds.x + bounds.w) {
			if (mouseCoords.y >= bounds.y && mouseCoords.y <= bounds.y + bounds.h) {
				if (brushButtons[i].getID() == 0) {
					brushSize = glm::clamp(brushSize + BRUSH_INCREMENT, 1, 10);
				}
				else {
					brushSize = glm::clamp(brushSize - BRUSH_INCREMENT, 1, 10);
				}
				return true;
			}
		}
	}

	return false;
}

// getters
std::vector<Component> MainPanel::getPanels() const {
	return panels;
}

std::vector<Component> MainPanel::getColorButtons() const {
	return colorButtons;
}

std::vector<Component> MainPanel::getBrushButtons() const {
	return brushButtons;
}

int MainPanel::getBrushSize() const {
	return brushSize;
}

Color MainPanel::getSelectedColor() const {
	return color;
}

// setters
void MainPanel::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}