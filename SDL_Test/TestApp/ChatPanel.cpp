#include "ChatPanel.h"
#include "Config.h"
#include "Color.h"
#include <iostream>

ChatPanel::ChatPanel() : offsetY(0) {
	init();
}

void ChatPanel::init() {
	setPosition(glm::ivec2(CHAT_PANEL_START_X, CHAT_PANEL_START_Y));
	setDimension(glm::ivec2(CHAT_PANEL_WIDTH, CHAT_PANEL_HEIGHT));
	setChange(true);
}

void ChatPanel::draw() {
	if (change) {
		// repaint background
		SDL_Rect bounds = {CHAT_PANEL_START_X, CHAT_PANEL_START_Y, CHAT_PANEL_WIDTH, TEXT_PANEL_HEIGHT + TTF_FontHeight(font->getFont())};
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &bounds);

		// draw chatPanel
		drawChatPanel();

		// draw subPanels
		drawSubPanels();

		// draw messages
		drawMessages();

		setChange(false);
	}
}

void ChatPanel::drawChatPanel() {
	SDL_Rect bounds = { position.x, position.y, dimension.x, dimension.y };
	Color c = BLACK;
	SDL_SetRenderDrawColor(renderer, c.getR(), c.getG(), c.getB(), c.getA());
	SDL_RenderDrawRect(renderer, &bounds);
}

void ChatPanel::drawSubPanels() {
	Color c = BLACK;

	// draw textPanel
	SDL_Rect bounds = { TEXT_PANEL_START_X, TEXT_PANEL_START_Y, TEXT_PANEL_WIDTH, TEXT_PANEL_HEIGHT };
	SDL_SetRenderDrawColor(renderer, c.getR(), c.getG(), c.getB(), c.getA());
	SDL_RenderDrawRect(renderer, &bounds);

	// draw inputPanel
	bounds = { INPUT_PANEL_START_X, INPUT_PANEL_START_Y, INPUT_PANEL_WIDTH, INPUT_PANEL_HEIGHT };
	SDL_SetRenderDrawColor(renderer, c.getR(), c.getG(), c.getB(), c.getA());
	SDL_RenderDrawRect(renderer, &bounds);
}

void ChatPanel::drawMessages() {
	if (offsetY > TEXT_PANEL_START_Y + TEXT_PANEL_HEIGHT - 2 * TTF_FontHeight(font->getFont())) {
		messages.pop();
	}

	std::queue<std::string> temp = messages;

	int i = 0;

	while (!temp.empty()) {
		std::string text = temp.front();

		SDL_Texture* texture = nullptr;
		SDL_Rect bounds;

		offsetY = TEXT_PANEL_START_Y + i * TTF_FontHeight(font->getFont());

		font->obtainTextData(text, BLACK, renderer, &texture, &bounds, glm::ivec2(TEXT_PANEL_START_X + 3, offsetY));

		SDL_RenderCopy(renderer, texture, NULL, &bounds);
		SDL_DestroyTexture(texture);

		temp.pop();

		i++;
	}
}

void ChatPanel::addMessage(std::string message) {
	messages.push(message);
}

void ChatPanel::setChange(bool change) {
	this->change = change;
}

void ChatPanel::update(Uint32 deltaTime) {
	change = true;
}

void ChatPanel::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void ChatPanel::setFont(Font* font) {
	this->font = font;
}


