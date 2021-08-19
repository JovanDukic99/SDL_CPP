#pragma once
#include "GUIBase.h"
#include "InputManager.h"
#include "Font.h"
#include <SDL/SDL_render.h>
#include <string>
#include <vector>
#include <queue>

class ChatPanel : GUIBase
{
private:
	SDL_Renderer* renderer;
	InputManager* inputManager;
	std::queue<std::string> messages;
	Font* font;
	bool change;
	int offsetY;
public:
	ChatPanel();

	void draw();
	void update(Uint32 deltaTime);

	void setRenderer(SDL_Renderer* renderer);
	void setFont(Font* font);
	void addMessage(std::string message);
private:
	void init();
	void drawChatPanel();
	void drawSubPanels();
	void drawMessages();
	void setChange(bool change);
};

