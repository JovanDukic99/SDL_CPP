#pragma once
#include "GUIBase.h"
#include "InputManager.h"
#include <SDL/SDL_render.h>
class ChatPanel : GUIBase
{
private:
	SDL_Renderer* renderer;
	InputManager* inputManager;
public:
	ChatPanel();

	void draw();
	void update(Uint32 deltaTime);

	void setRenderer(SDL_Renderer* renderer);
private:
	void init();
	void drawChatPanel();
	void drawSubPanels();
};

