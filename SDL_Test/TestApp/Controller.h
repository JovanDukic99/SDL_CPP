#pragma once

enum class State {
	NONE,
	DRAWING,
	ERASING,
	BUCKET_PAINTING
};

enum class ScreenState {
	FREEZE,
	REFRESH
};

class Controller
{
private:
	static Controller* INSTANCE;
	State state;
	ScreenState screenState;
private:
	Controller();
	~Controller();
public:
	static Controller* getInstance();

	// getters
	State getState() const;
	ScreenState getScreenState() const;

	// setters
	void setState(State state);
	void setScreenState(ScreenState screenState);
};

