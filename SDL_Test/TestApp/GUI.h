#pragma once
#include "Player.h"
#include "InputManager.h"
#include "MainPanel.h"
#include "HudBase.h"
#include <SDL/SDL.h>
#include <SDL_TTF/SDL_ttf.h>
#include <vector>
#include <string>

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
	TTF_Font* font;
	std::vector<SDL_Rect> blocks;
	bool shouldDrawRubber;
public:
	GUI();
	~GUI();
private:
	void init();
	void initSDL();
	void initTTF();
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
	void drawText();
	void drawText(std::string text, int x, int y);
	void drawText(SDL_Rect* position, std::string& text);
};

