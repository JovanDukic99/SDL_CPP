#pragma once
#include "Player.h"
#include "InputManager.h"
#include "MainPanel.h"
#include "HudBase.h"
#include <SDL/SDL.h>
#include <vector>

class GUI
{
private:
	enum class GameState {
		PLAY,
		EXIT
	};
private:
	SDL_Window* window;
	SDL_Surface* surface;
	SDL_Renderer* renderer;
	GameState gameState;
	Player player;
	InputManager inputManager;
	SDL_Rect rubber;
	MainPanel hudPanel;
	std::vector<SDL_Rect> blocks;
	bool shouldDrawRubber;
public:
	GUI();
	~GUI();
private:
	void init();
	void initSDL();
	void initComponents();
	void run();
	void handleInputEvents();
	void update();
	void draw();
	void drawGrid();
	void drawPlayer();
	void drawBlocks();
	void drawRubber();
	void drawHUD();
};

