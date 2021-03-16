#pragma once
#include "InputManager.h"
#include "MainPanel.h"
#include "ColorPicker.h"
#include <SDL/SDL.h>
#include <SDL_TTF/SDL_ttf.h>
#include <SDL_IMAGE/SDL_image.h>
#include <vector>
#include <stack>
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
	SDL_Renderer* renderer;
	GameState gameState;
	InputManager inputManager;
	ColorPicker colorPicker;
	SDL_Rect rubber;
	MainPanel mainPanel;
	TTF_Font* font;
	bool change;
public:
	GUI();
	~GUI();
private:
	void init();
	void initSDL();
	void initTTF();
	void initSDL_Image();
	void initComponents();
	void run();
	void handleInputEvents();
	void handleWindowEvents(SDL_Event& event);
	void update();
	bool updateColorPicker();
	void initDraw();
	void drawHUD();
	void drawCircle(int x, int y, int radius);
	void drawText();
	void drawText(std::string text, int x, int y);
	void drawText(SDL_Rect* position, std::string& text);
	void updateScreen();
};

