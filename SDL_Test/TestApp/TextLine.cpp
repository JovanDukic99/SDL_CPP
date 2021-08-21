#include "TextLine.h"
#include "Controller.h"
#include "Utils.h"
#include <iostream>

TextLine::TextLine(glm::ivec2 textPosition, int size, SDL_Renderer* renderer, Font* font) : textPosition(textPosition), size(size), font(font), cursorPosition(), deleteTimer(0), cursorTimer(0), inputManager(nullptr), renderer(renderer) {
	init();
}

TextLine::~TextLine() {
	reset();
}

void TextLine::draw() {
	drawText();
	drawCursor();
}

void TextLine::update(Uint32 deltaTime) {
	updateText(deltaTime);
	updateCursor();
}

int TextLine::getSize() {
	return text.size();
}

void TextLine::init() {
	inputManager = Controller::getInstance()->getInputManager();
}

void TextLine::reset() {
	font = nullptr;
	inputManager = nullptr;
	renderer = nullptr;
}

void TextLine::updateText(Uint32 deltaTime) {
	if (inputManager->isAppend() && text.size() < size) {
		text += inputManager->getText();
	}
	else if (inputManager->isKeyPressed(SDLK_BACKSPACE) && deleteTimer >= 1000 && !text.empty()) {
		text.erase(text.size() - 1);
	}
	else if (inputManager->isKeyPressed(SDLK_BACKSPACE) && deleteTimer == 0 && !text.empty()) {
		text.erase(text.size() - 1);
		deleteTimer += deltaTime;
	}
	else if (inputManager->isKeyPressed(SDLK_BACKSPACE) && deleteTimer < 1000) {
		deleteTimer += deltaTime;
	}
	else if (!inputManager->isKeyPressed(SDLK_BACKSPACE) && deleteTimer != 0) {
		deleteTimer = 0;
	}
}

void TextLine::updateCursor() {
	if (!text.empty()) {
		glm::ivec2 textDimensions = font->getTextDimensions(text);
		cursorPosition = { textDimensions.x, textDimensions.y };
	}
	else {
		cursorPosition = { 0, font->getTextHeight() };
	}
}

void TextLine::drawText() {
	if (!text.empty()) {
		Utils::drawText(text, BLACK, renderer, font, textPosition);
	}
}

void TextLine::drawCursor() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, textPosition.x + cursorPosition.x, textPosition.y, textPosition.x + cursorPosition.x, textPosition.y + cursorPosition.y);
}
