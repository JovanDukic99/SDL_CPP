#pragma once
#include "InputManager.h"
#include "MainPanel.h"
#include "ColorPicker.h"
#include "Font.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>
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
	Font font;
	SDL_Rect rubber;
	MainPanel mainPanel;
	glm::ivec2 start;
	glm::ivec2 end;
	bool change;
public:
	GUI();
	~GUI();
private:
	void init();
	void initSDL();
	void initTTF();
	void initFont();
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
	void updateScreen();
};

