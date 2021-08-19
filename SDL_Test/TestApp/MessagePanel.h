#pragma once
#include "Font.h"
#include "Component.h"
#include "InputManager.h"
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
#include <glm/glm.hpp>

class MessagePanel
{
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	InputManager* inputManager;
	Font* font;
	glm::ivec4 button;
	Color buttonColor;
	bool isPressed;
	std::string message;
	bool visible;
public:
	MessagePanel();
	~MessagePanel();
	void init(std::string message, Font* font, InputManager* inputManager);
	void setMessage(std::string message);
	void setFont(Font* font);
	void setInputManager(InputManager* inputManager);
	void draw();
	void update();
	bool isVisible();
	void closeWindow();
private:
	void initWindow();
	void initRenderer();
	void initComponents();
	void setVisible(bool visible);
	void setIsPressed(bool isPressed);
	void setButtonColor(Color color);
	void reset();
};

