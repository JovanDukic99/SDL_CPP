#include "ColorPicker.h"
#include "Config.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <iostream>

ColorPicker::ColorPicker() : window(nullptr), renderer(nullptr), visible(false), clickedRed(false), clickedGreen(false), clickedBlue(false) {

}

ColorPicker::~ColorPicker() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	setVisible(false);
}

void ColorPicker::init() {
	initWindow();
	initComponents();
	draw();
	setVisible(true);
}

void ColorPicker::initWindow() {
	// create window
	if (window == nullptr) {
		window = SDL_CreateWindow(COLOR_PICKER.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, COLOR_PICKER_WIDTH, COLOR_PICKER_HEIGHT, SDL_WINDOW_SHOWN);
	}

	if (window == nullptr) {
		std::cout << "Color picker creation failed." << std::endl;
		return;
	}

	// create renderer
	if (renderer == nullptr) {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	}

	if (renderer == nullptr) {
		std::cout << "Color picker renderer failed to be created." << std::endl;
		return;
	}
}

void ColorPicker::initComponents() {
	// init colorPanel bounds
	SDL_Rect colorPanelBounds;

	colorPanelBounds.w = COLOR_PICKER_COLOR_PANEL_WIDTH;
	colorPanelBounds.h = COLOR_PICKER_COLOR_PANEL_HEIGHT;

	colorPanelBounds.x = COLOR_PICKER_COLOR_PANEL_START_X;
	colorPanelBounds.y = COLOR_PICKER_COLOR_PANEL_START_Y;

	colorPanel.init(colorPanelBounds, BLACK);

	// init red toggleButton
	SDL_Rect toggleBounds;

	toggleBounds.w = TOGGLE_BUTTON_WIDTH;
	toggleBounds.h = TOGGLE_BUTTON_HEIGHT;

	toggleBounds.x = RED_TOGGLE_BUTTON_START_X;
	toggleBounds.y = RED_TOGGLE_BUTTON_START_Y - toggleBounds.h / 2;

	toggleRed.init(toggleBounds, BLACK);

	// init green toggleButton
	toggleBounds.x = GREEN_TOGGLE_BUTTON_START_X;
	toggleBounds.y = GREEN_TOGGLE_BUTTON_START_Y - toggleBounds.h / 2;

	toggleGreen.init(toggleBounds, BLACK);

	// init blue toogleButton
	toggleBounds.x = BLUE_TOGGLE_BUTTON_START_X;
	toggleBounds.y = BLUE_TOGGLE_BUTTON_START_Y - toggleBounds.h / 2;

	toggleBlue.init(toggleBounds, BLACK);
}

// update
void ColorPicker::update(InputManager inputManager) {
	glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

	if (!inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		reset();
		return;
	}

	// check if user is scrolling left or right
	if (clickedRed == true) {
		updateToggleButton(mouseCoords, &toggleRed);
		draw();
		return;
	}
	else if (clickedGreen == true) {
		updateToggleButton(mouseCoords, &toggleGreen);
		draw();
		return;
	}
	else if (clickedBlue == true) {
		updateToggleButton(mouseCoords, &toggleBlue);
		draw();
		return;
	}

	// update toggleRed
	if (Utils::isPointInsideBounds(mouseCoords, toggleRed.getBounds())) {
		clickedRed = true;
		return;
	}

	// update toggleGreen
	if (Utils::isPointInsideBounds(mouseCoords, toggleGreen.getBounds())) {
		clickedGreen = true;
		return;
	}

	// update toggleBlue
	if (Utils::isPointInsideBounds(mouseCoords, toggleBlue.getBounds())) {
		clickedBlue = true;
		return;
	}
}

void ColorPicker::updateToggleButton(glm::ivec2 mouseCoords, Component* toggleButton) {
	SDL_Rect bounds = toggleButton->getBounds();
	bounds.x = mouseCoords.x - bounds.w / 2;
	toggleButton->setBounds(bounds);
}

void ColorPicker::draw() {
	// draw background
	SDL_SetRenderDrawColor(renderer, 255, 255, 255 ,255);
	SDL_RenderFillRect(renderer, NULL);

	// draw colorPanel border
	SDL_Rect bounds = colorPanel.getBounds();
	Color color = BLACK;

	bounds.x = bounds.x - 5;
	bounds.y = bounds.y - 5;

	bounds.w = bounds.w + 10;
	bounds.h = bounds.h + 10;

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderFillRect(renderer, &bounds);

	// draw colorPanel
	bounds = colorPanel.getBounds();
	color = colorPanel.getColor();

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderFillRect(renderer, &bounds);

	// draw red interval
	color = RED;

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderDrawLine(renderer, COLOR_INTERVAL_START_X, COLOR_INTERVAL_START_Y, COLOR_INTERVAL_END_X, COLOR_INTERVAL_END_Y);

	// draw green interval
	color = GREEN;

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderDrawLine(renderer, COLOR_INTERVAL_START_X, COLOR_INTERVAL_START_Y + COLOR_INTERVAL_HORIZONTAL_OFFSET, COLOR_INTERVAL_END_X, COLOR_INTERVAL_END_Y + COLOR_INTERVAL_HORIZONTAL_OFFSET);

	// draw blue interval
	color = BLUE;

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderDrawLine(renderer, COLOR_INTERVAL_START_X, COLOR_INTERVAL_START_Y + 2 * COLOR_INTERVAL_HORIZONTAL_OFFSET, COLOR_INTERVAL_END_X, COLOR_INTERVAL_END_Y + 2 * COLOR_INTERVAL_HORIZONTAL_OFFSET);

	// draw red toggleButton
	bounds = toggleRed.getBounds();
	color = toggleRed.getColor();

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderFillRect(renderer, &bounds);

	// draw green toggleButton
	bounds = toggleGreen.getBounds();
	color = toggleGreen.getColor();

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderFillRect(renderer, &bounds);

	// draw blue toggleButton
	bounds = toggleBlue.getBounds();
	color = toggleBlue.getColor();

	SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderFillRect(renderer, &bounds);

	// update screen
	SDL_RenderPresent(renderer);
}

void ColorPicker::closeWindow() {
	ColorPicker::~ColorPicker();
}

// setters
void ColorPicker::setVisible(bool visible) {
	this->visible = visible;
}

void ColorPicker::reset() {
	clickedRed = false;
	clickedGreen = false;
	clickedBlue = false;
}

// getters
bool ColorPicker::isVisible() const {
	return visible;
}
