#pragma once
#include "Component.h"
#include "InputManager.h"
#include "Color.h"
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
#include <SDL_TTF/SDL_ttf.h>
#include <string>
class ColorPicker
{
private:
	enum class Factor {
		R,
		G,
		B
	};
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	Component colorPanel;
	Component submitButton;

	Component toggleRed;
	Component toggleGreen;
	Component toggleBlue;

	TTF_Font* font;
	TTF_Font* submitFont;
	int xMin1, xMax1, yMin1, yMax1, advance1;
	int xMin2, xMax2, yMin2, yMax2, advance2;

	std::string redLabel;
	std::string greenLabel;
	std::string blueLabel;

	Color color;

	bool clickedRed;
	bool clickedGreen;
	bool clickedBlue;
	bool clickedSubmit;
	bool hasReset;
	bool visible;
public:
	// constructors
	ColorPicker();
	~ColorPicker();

	// init
	void init(Color color);

	// update
	void update(InputManager inputManager);

	// setters
	void closeWindow();

	// getters
	bool isVisible() const;
	Color getColor() const;
private:
	// init
	void initWindow();
	void initComponents(Color color);
	void initFont();

	// update
	void updateToggleButton(glm::ivec2 mouseCoords, Component* toggleButton);
	void updateColor(glm::ivec2 mouseCoords, Factor factor);
	void updateColorPanel();

	// setters
	void setVisible(bool visible);
	void setColor(Color color);
	void reset();
	void resetClass();

	// getters
	SDL_Rect textBounds(std::string text, int x, int y, int xMax, int xMin, int yMax, int yMin, int advance);
	SDL_Rect textBounds(int x, int y, int widht, int height);

	// draw
	void draw();
};

