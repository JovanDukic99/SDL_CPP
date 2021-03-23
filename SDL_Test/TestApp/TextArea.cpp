#include "TextArea.h"
#include "Config.h"
#include <iostream>

TextArea::TextArea(glm::ivec2 position, Color color, Font font, SDL_Renderer* renderer) : font(font), color(color), renderer(renderer), indicatorPosition(position), indicatorState(IndicatorState::NONE), indicatorTimer(0), indicatorIndex(0), show(true), index(0) {
	setPosition(position);
	takeScreenshot();
	textPositions.emplace_back(position);
	textLines.emplace_back("");
}

TextArea::~TextArea() {
	hideIndicator();
}

void TextArea::draw() {
	drawText();
	drawIndicator();
}

void TextArea::takeScreenshot() {
	SDL_Surface* sshot = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT - MAIN_PANEL_HEIGHT, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);

	SDL_Rect rect = { 0, MAIN_PANEL_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - MAIN_PANEL_HEIGHT };

	SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);

	if ((screenshot = SDL_CreateTextureFromSurface(renderer, sshot)) == nullptr) {
		std::cout << "Screenshot creation failed." << std::endl;
	}

	SDL_FreeSurface(sshot);
}

void TextArea::drawScreenshot() {
	SDL_Rect dest = { 0, MAIN_PANEL_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - MAIN_PANEL_HEIGHT };
	SDL_RenderCopy(renderer, screenshot, NULL, &dest);
}

void TextArea::updateIndicatorTimer(Uint32 deltaTime) {
	indicatorTimer += deltaTime;
}

void TextArea::updateText() {
	if (inputManager->isAppend()) {
		std::string newText = inputManager->getText();
		for (size_t i = 0; i < newText.size(); i++) {
			textLines[index].insert(textLines[index].begin() + indicatorIndex, newText[i]);
			moveIndicatorRight();
			increaseIndicatorPos();
		}
	}
}

bool TextArea::isLeft() const {
	return indicatorState == IndicatorState::LEFT;
}

bool TextArea::isRight() const {
	return indicatorState == IndicatorState::RIGHT;
}

bool TextArea::isBackspace() const {
	return indicatorState == IndicatorState::BACKSPACE;
}

bool TextArea::isEnter() const {
	return indicatorState == IndicatorState::ENTER;
}

bool TextArea::removeCharacter() {
	if (indicatorIndex > 0) {
		decreaseIndicatorPos();
		moveIndicatorLeft();
		textLines[index].erase(textLines[index].begin() + indicatorIndex);
		return true;
	}
	else if(index - 1 >= 0 ) {
		index--;
		indicatorIndex = textLines[index].size();
		indicatorPosition = position;
	}
	return false;
}

void TextArea::setIndicatorState(IndicatorState indicatorState) {
	this->indicatorState = indicatorState;
}

void TextArea::changeState(IndicatorState indicatorState) {
	buttonTimer = 0;
	inputManager->setAppend(true);
	setIndicatorState(indicatorState);
}

bool TextArea::increaseIndicatorPos() {
	if (indicatorIndex + 1 <= textLines[index].size()) {
		indicatorIndex++;
		return true;
	}
	return false;
}

bool TextArea::decreaseIndicatorPos() {
	if (indicatorIndex - 1 >= 0) {
		indicatorIndex--;
		return true;
	}
	return false;
}

void TextArea::leftAction(Uint32 deltaTime) {
	if (buttonTimer > 700 && decreaseIndicatorPos()) {
		hideIndicator();
		moveIndicatorLeft();
	}
	else {
		buttonTimer += deltaTime;
	}
}

void TextArea::rightAction(Uint32 deltaTime) {
	if (buttonTimer > 700) {
		hideIndicator();
		moveIndicatorRight();
		increaseIndicatorPos();
	}
	else {
		buttonTimer += deltaTime;
	}
}


void TextArea::backspaceAction(Uint32 deltaTime) {
	if (buttonTimer > 1000 && removeCharacter()) {
		inputManager->setAppend(true);
	}
	else {
		buttonTimer += deltaTime;
	}
}

void TextArea::moveIndicatorLeft() {
	if (indicatorIndex > 0) {
		int minx, maxx, miny, maxy, advance;
		TTF_GlyphMetrics(font.getFont(), textLines[index].at(indicatorIndex), &minx, &maxx, &miny, &maxy, &advance);
		indicatorPosition.x = indicatorPosition.x - advance;
	}
	else {
		indicatorPosition = textPositions[index];
	}
}

void TextArea::moveIndicatorRight() {
	if (indicatorIndex < textLines[index].size()) {
		int minx, maxx, miny, maxy, advance;
		TTF_GlyphMetrics(font.getFont(), textLines[index].at(indicatorIndex), &minx, &maxx, &miny, &maxy, &advance);
		indicatorPosition.x = indicatorPosition.x + advance;
	}
}

void TextArea::setRepaint(bool repaint) {
	this->repaint = repaint;
}

void TextArea::drawText() {
	if (inputManager->isAppend()) {
		drawScreenshot();

		for (size_t i = 0; i <= index; i++) {
			std::string currentLine = textLines[i];
			glm::ivec2 currentPosition = textPositions[i];

			if (currentLine.empty()) {
				continue;
			}

			SDL_Texture* fontTexture = nullptr;
			SDL_Rect textBounds;

			font.obtainTextData(currentLine, color, renderer, &fontTexture, &textBounds, currentPosition);
			setDimension(glm::ivec2(textBounds.w, textBounds.h));

			textBounds.y = textBounds.y - textBounds.h / 2;

			SDL_RenderCopy(renderer, fontTexture, NULL, &textBounds);
			SDL_DestroyTexture(fontTexture);
		}
	}
}

void TextArea::drawIndicator() {
	if (indicatorTimer > 500) {
		if (show) {
			showIndicator();
		}
		else {
			hideIndicator();
		}
		indicatorTimer = 0;
	}
}

void TextArea::showIndicator() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawLine(renderer, indicatorPosition.x, indicatorPosition.y - 10, indicatorPosition.x, indicatorPosition.y + 10);
	show = false;
}

void TextArea::hideIndicator() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, indicatorPosition.x, indicatorPosition.y - 10, indicatorPosition.x, indicatorPosition.y + 10);
	show = true;
}

void TextArea::update(Uint32 deltaTime) {
	updateIndicatorTimer(deltaTime);
	updateText();

	if (!isBackspace() && inputManager->isKeyPressed(SDLK_BACKSPACE) && removeCharacter()) {
		changeState(IndicatorState::BACKSPACE);
	}
	else if (!isLeft() && inputManager->isKeyPressed(SDLK_LEFT) && decreaseIndicatorPos()) {
		hideIndicator();
		moveIndicatorLeft();
		changeState(IndicatorState::LEFT);
	}
	else if (!isRight() && inputManager->isKeyPressed(SDLK_RIGHT)) {
		hideIndicator();
		moveIndicatorRight();
		increaseIndicatorPos();
		changeState(IndicatorState::RIGHT);
	}
	else if (isBackspace() && inputManager->isKeyPressed(SDLK_BACKSPACE)) {
		backspaceAction(deltaTime);
	}
	else if (isLeft() && inputManager->isKeyPressed(SDLK_LEFT)) {
		leftAction(deltaTime);
	}
	else if (isRight() && inputManager->isKeyPressed(SDLK_RIGHT)) {
		rightAction(deltaTime);
	}
	else if (!inputManager->isKeyPressed(SDLK_RIGHT) && isRight()) {
		setIndicatorState(IndicatorState::NONE);
	}
	else if (!inputManager->isKeyPressed(SDLK_LEFT) && isLeft()) {
		setIndicatorState(IndicatorState::NONE);
	}
	else if (!inputManager->isKeyPressed(SDLK_BACKSPACE) && isBackspace()) {
		setIndicatorState(IndicatorState::NONE);
	}
	else if (!inputManager->isKeyPressed(SDLK_RETURN) && isEnter()) {
		setIndicatorState(IndicatorState::NONE);
	}
	else if (!isEnter() && inputManager->isKeyPressed(SDLK_RETURN)) {
		hideIndicator();

		index++;
		indicatorPosition = glm::ivec2(position.x, indicatorPosition.y + TTF_FontHeight(font.getFont()));
		indicatorIndex = 0;

		textPositions.emplace_back(indicatorPosition);
		textLines.emplace_back("");

		setIndicatorState(IndicatorState::ENTER);
	}
}

