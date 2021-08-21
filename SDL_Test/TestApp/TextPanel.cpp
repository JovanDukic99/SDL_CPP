#include "TextPanel.h"
#include "Utils.h"
#include "Config.h"
#include <iostream>

TextPanel::TextPanel() : Window(), font(nullptr), button(), buttonColor(GRAY), pressed(false), textLine(nullptr) {

}

TextPanel::~TextPanel() {
	closeWindow();
}

void TextPanel::init(Font* font) {
	Window::init("Start", glm::ivec2(500, 300));
	setFont(font);
	initComponents();
}

void TextPanel::initComponents() {
	button = {150, 200, 200, 50};

	if (textLine == nullptr) {
		textLine = new TextLine(glm::ivec2(100, 100), 5, renderer, font);
	}
}

void TextPanel::draw() {
	// draw panel background
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_RenderFillRect(renderer, NULL);

	// draw submit button
	Utils::drawButton(buttonColor, "Submit", BLACK, renderer, font, button);

	// draw text 
	Utils::drawText("Unesite vase ime", BLACK, renderer, font, glm::ivec2(150, 50));

	// drawText area
	if (textLine != nullptr) {
		textLine->draw();
	}

	SDL_RenderPresent(renderer);
}

void TextPanel::update() {
	if (isPressed() && !inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
		closeWindow();
	}
	else if (inputManager->isKeyPressed(SDL_BUTTON_LEFT) && Utils::isPointInsideBounds(inputManager->getMouseCoordinates(), button)) {
		setButtonColor(YELLOW_GREEN);
		setPressed(true);
	}
	
	if (textLine != nullptr) {
		textLine->update(DESIRED_FRAME_TIME);
	}
}

void TextPanel::setFont(Font* font) {
	this->font = font;
}

void TextPanel::closeWindow() {
	close();
	resetTextLine();
	setPressed(false);
}

void TextPanel::setPressed(bool pressed) {
	this->pressed = pressed;
}

void TextPanel::setButtonColor(Color color) {
	this->buttonColor = color;
}

void TextPanel::resetTextLine() {
	delete textLine;
	textLine = nullptr;
}

bool TextPanel::isPressed() {
	return pressed;
}
