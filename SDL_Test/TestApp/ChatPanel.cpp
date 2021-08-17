#include "ChatPanel.h"
#include "Config.h"
#include "Color.h"

ChatPanel::ChatPanel() {
	init();
}

void ChatPanel::init() {
	setPosition(glm::ivec2(CHAT_PANEL_START_X, CHAT_PANEL_START_Y));
	setDimension(glm::ivec2(CHAT_PANEL_WIDTH, CHAT_PANEL_HEIGHT));
}

void ChatPanel::draw() {
	// draw chatPanel
	drawChatPanel();

	// draw subPanels
	drawSubPanels();
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

void ChatPanel::update(Uint32 deltaTime) {

}

void ChatPanel::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}


