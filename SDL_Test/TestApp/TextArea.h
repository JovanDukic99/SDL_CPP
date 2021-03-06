#pragma once
#include "Font.h"
#include "Color.h"
#include "GUIBase.h"
#include "ChatPanel.h"
#include <glm/glm.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_render.h>
#include <vector>
#include <string>

class TextArea : public GUIBase
{
private:
	enum class IndicatorState {
		NONE,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		BACKSPACE,
		ENTER
	};
private:
	glm::ivec2 indicatorPosition;
	std::vector<glm::ivec2> textPositions; // posiiton of text in rows
	std::vector<glm::ivec2> dimensions; // text dimensions
	std::vector<std::string> textLines; // text
	int maxIndex;
	int index;
	int indicatorIndex;
	bool show;
	Uint32 buttonTimer;
	Uint32 indicatorTimer;
	ChatPanel* chatPanel;
	Color color;
	Font font;
	IndicatorState indicatorState;
	SDL_Renderer* renderer;
	SDL_Texture* screenshot;
public:
	TextArea(glm::ivec2 position, Color color, Font font, SDL_Renderer* renderer);
	~TextArea();

	void draw();
	void update(Uint32 deltaTime);
	void setChatPanel(ChatPanel* chatPanel);
private:
	void drawText();
	void drawTextBounds();
	void drawIndicator();
	void showIndicator();
	void hideIndicator();

	void takeScreenshot();
	void drawScreenshot();

	void updateIndicatorTimer(Uint32 deltaTime);
	void updateText();

	bool isLeft() const;
	bool isRight() const;
	bool isBackspace() const;
	bool isEnter() const;
	bool isUp() const;
	bool isDown() const;
	bool removeCharacter();

	void setIndicatorState(IndicatorState indicatorState);
	void changeState(IndicatorState indicatorState);
	bool increaseIndicatorPos();
	bool decreaseIndicatorPos();
	void leftAction(Uint32 deltaTime);
	void rightAction(Uint32 deltaTime);
	void rightDown();
	void upAction();
	void downAction();
	void enterAction();
	void backspaceAction(Uint32 deltaTime);
	void newLine();
	void moveIndicatorLeft();
	void moveIndicatorRight();
};

