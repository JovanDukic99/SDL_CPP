#pragma once
#include "InputManager.h"
#include "MainPanel.h"
#include "ColorPicker.h"
#include "Font.h"
#include "Controller.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <SDL_IMAGE/SDL_image.h>
#include <vector>
#include <stack>
#include <string>

class MainFrame
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
	Controller* controller;
	Font font;
	SDL_Rect rubber;
	MainPanel mainPanel;
	glm::ivec2 start;
	glm::ivec2 end;
public:
	MainFrame();
	~MainFrame();
private:
	void init();
	void initSDL();
	void initTTF();
	void initFont();
	void initSDL_Image();
	void initController();
	void initComponents();
	void run();
	void handleInputEvents();
	void handleWindowEvents(SDL_Event& event);
	void update();
	bool updateColorPicker();
	void initDraw();
	void drawHUD();
	void updateCursor();
	void drawCircle(int x, int y, int radius);
	void updateScreen();
	bool refresh();
};

