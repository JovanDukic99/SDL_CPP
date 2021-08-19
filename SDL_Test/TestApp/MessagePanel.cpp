#include "MessagePanel.h"
#include "Config.h"
#include "Utils.h"
#include <iostream>

MessagePanel::MessagePanel() : window(nullptr), renderer(nullptr), font(nullptr), inputManager(nullptr), button(), visible(false), buttonColor(GRAY), isPressed(false) {

}

MessagePanel::~MessagePanel() {
	closeWindow();
}

void MessagePanel::init(std::string message, Font* font, InputManager* inputManager) {
	initWindow();
	initRenderer();
	initComponents();
	setMessage(message);
	setFont(font);
	setInputManager(inputManager);
	setVisible(true);
}

void MessagePanel::initWindow() {
	window = Utils::createWindow("Notification!");
}

void MessagePanel::initRenderer(){
	renderer = Utils::createRenderer(window);
}

void MessagePanel::initComponents() {
	button = { 200, 200, 100, 50 };
}

void MessagePanel::reset() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	
}

void MessagePanel::setMessage(std::string message) {
	this->message = message;
}

void MessagePanel::setFont(Font* font) {
	this->font = font;
}

void MessagePanel::setInputManager(InputManager* inputManager) {
	this->inputManager = inputManager;
}

void MessagePanel::draw() {
	// draw background color
	Color c = WHITE;
	SDL_SetRenderDrawColor(renderer, c.getR(), c.getG(), c.getB(), c.getA());
	SDL_RenderFillRect(renderer, NULL);
	
	// draw the message
	Utils::drawText(message, BLACK, renderer, font, glm::ivec2(0, MESSAGE_PANEL_HEIGHT / 4), MESSAGE_PANEL_WIDTH);

	// draw button
	Utils::drawButton(buttonColor, "OK", BLACK, renderer, font, button);

	// refresh the screen
	SDL_RenderPresent(renderer);
}

void MessagePanel::update() {
	if (isPressed && !inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
		closeWindow();
	}else if (inputManager->isKeyPressed(SDL_BUTTON_LEFT) && Utils::isPointInsideBounds(inputManager->getMouseCoordinates(), button)) {
		setButtonColor(YELLOW_GREEN);
		setIsPressed(true);
	}
}

bool MessagePanel::isVisible() {
	return visible;
}

void MessagePanel::setVisible(bool visible) {
	this->visible = visible;
}

void MessagePanel::setIsPressed(bool isPressed) {
	this->isPressed = isPressed;
}

void MessagePanel::setButtonColor(Color color) {
	this->buttonColor = color;
}

void MessagePanel::closeWindow() {
	reset();
	setVisible(false);
	setIsPressed(false);
	setButtonColor(GRAY);
}
