#include "TextArea.h"
#include "Config.h"
#include <iostream>

TextArea::TextArea(glm::ivec2 position, Color color, Font font, SDL_Renderer* renderer) : font(font), color(color), renderer(renderer), indicatorPosition(position), indicatorState(IndicatorState::NONE), indicatorTimer(0), indicatorIndex(0), show(true), index(0), maxIndex(0) {
	setPosition(position);
	takeScreenshot();
	textPositions.emplace_back(position);
	dimensions.emplace_back(glm::ivec2(0, 0));
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

bool TextArea::isUp() const {
	return indicatorState == IndicatorState::UP;
}

bool TextArea::isDown() const {
	return indicatorState == IndicatorState::DOWN;
}

bool TextArea::removeCharacter() {
	if (indicatorIndex > 0) {
		decreaseIndicatorPos();
		moveIndicatorLeft();
		textLines[index].erase(textLines[index].begin() + indicatorIndex); // 0 1 2 3
		return true;
	}else if (index > 0 && index < textPositions.size()) {
		int verticalOffset = TTF_FontHeight(font.getFont());
		for (size_t i = index + 1; i < textPositions.size(); i++) {
			textPositions[i].y = textPositions[i].y - verticalOffset;
		}

		textLines.erase(textLines.begin() + index);
		dimensions.erase(dimensions.begin() + index);
		textPositions.erase(textPositions.begin() + index);

		if (index - 1 >= 0) {
			index--;
			maxIndex--;
			indicatorIndex = textLines[index].size();
			indicatorPosition = textPositions[index];
			indicatorPosition.x += dimensions[index].x;
		}

		return true;
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

void TextArea::rightDown() {
	hideIndicator();

	if (index + 1 <= maxIndex) {
		index++;
		indicatorIndex = 0;
		indicatorPosition = textPositions[index];
	}
}

void TextArea::upAction() {
	hideIndicator();

	if (index - 1 >= 0) {
		index--;
		indicatorIndex = textLines[index].size();
		indicatorPosition = textPositions[index];
		indicatorPosition.x += dimensions[index].x;
	}
}

void TextArea::downAction() {
	hideIndicator();

	if (index + 1 <= maxIndex) {
		index++;
		indicatorIndex = textLines[index].size();
		indicatorPosition = textPositions[index];
		indicatorPosition.x += dimensions[index].x;
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

void TextArea::enterAction() {
	hideIndicator();

	index++;
	indicatorPosition = glm::ivec2(position.x, indicatorPosition.y + TTF_FontHeight(font.getFont())); // 0 1 2 3
	indicatorIndex = 0;

	if (index < textPositions.size()) {
		int verticalOffset = TTF_FontHeight(font.getFont());
		for (size_t i = index; i <= maxIndex; i++) {
			textPositions[i].y = textPositions[i].y + verticalOffset;
		}
	}

	textPositions.insert(textPositions.begin() + index, indicatorPosition);
	dimensions.insert(dimensions.begin() + index, glm::ivec2(0, 0));
	textLines.insert(textLines.begin() + index, "");

	maxIndex++;

	inputManager->setAppend(true);
	setIndicatorState(IndicatorState::ENTER);
}

void TextArea::moveIndicatorLeft() {
	if (indicatorIndex >= 0) {
		int minx, maxx, miny, maxy, advance;
		TTF_GlyphMetrics(font.getFont(), textLines[index].at(indicatorIndex), &minx, &maxx, &miny, &maxy, &advance);
		indicatorPosition.x = indicatorPosition.x - advance;
	}
	else {
		indicatorPosition.x = textPositions[index].x;
	}
}

void TextArea::moveIndicatorRight() {
	if (indicatorIndex < textLines[index].size()) {
		int minx, maxx, miny, maxy, advance;
		TTF_GlyphMetrics(font.getFont(), textLines[index].at(indicatorIndex), &minx, &maxx, &miny, &maxy, &advance);
		indicatorPosition.x = indicatorPosition.x + advance;
	}
}

void TextArea::drawText() {
	if (inputManager->isAppend()) {
		drawScreenshot();

		dimension = glm::ivec2(0, 0);

		for (size_t i = 0; i <= maxIndex; i++) {
			std::string currentLine = textLines[i];
			glm::ivec2 currentPosition = textPositions[i];

			if (currentLine.empty()) {
				dimension.y += TTF_FontHeight(font.getFont());
				continue;
			}

			SDL_Texture* fontTexture = nullptr;
			SDL_Rect textBounds;

			font.obtainTextData(currentLine, color, renderer, &fontTexture, &textBounds, currentPosition);
			dimensions[i] = glm::ivec2(textBounds.w, textBounds.h);

			if (textBounds.w > dimension.x) {
				dimension.x = textBounds.w;
			}

			dimension.y += textBounds.h;

			textBounds.y = textBounds.y - textBounds.h / 2;

			SDL_RenderCopy(renderer, fontTexture, NULL, &textBounds);
			SDL_DestroyTexture(fontTexture);
		}

		if (dimension.x > 0) {
			drawTextBounds();
		}
	}
}

void TextArea::drawTextBounds() {
	SDL_Rect textBounds = { position.x - 5, position.y - 20, dimension.x + 10, dimension.y + 5 }; // dimension.y + 5 bcs. of q and g
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &textBounds);
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
	else if (!isLeft() && inputManager->isKeyPressed(SDLK_LEFT)) {
		if (decreaseIndicatorPos()) {
			hideIndicator();
			moveIndicatorLeft();
		}
		else {
			upAction();
		}
		changeState(IndicatorState::LEFT);
	}
	else if (!isRight() && inputManager->isKeyPressed(SDLK_RIGHT)) {
		hideIndicator();
		moveIndicatorRight();

		if (!increaseIndicatorPos()) {
			rightDown();
		}

		changeState(IndicatorState::RIGHT);
	}
	else if (!isUp() && inputManager->isKeyPressed(SDLK_UP)) {
		upAction();
		changeState(IndicatorState::UP);
	}
	else if (!isDown() && inputManager->isKeyPressed(SDLK_DOWN)) {	
		downAction();
		changeState(IndicatorState::DOWN);
	}
	else if (!isEnter() && (inputManager->isKeyPressed(SDLK_RETURN) || inputManager->isKeyPressed(SDLK_KP_ENTER))) {
		enterAction();
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
	else if ((!inputManager->isKeyPressed(SDLK_RETURN) && !inputManager->isKeyPressed(SDLK_KP_ENTER)) && isEnter()) {
		setIndicatorState(IndicatorState::NONE);
	}
	else if (!inputManager->isKeyPressed(SDLK_UP) && isUp()) {
		setIndicatorState(IndicatorState::NONE);
	}
	else if (!inputManager->isKeyPressed(SDLK_DOWN) && isDown()) {
		setIndicatorState(IndicatorState::NONE);
	}
}

