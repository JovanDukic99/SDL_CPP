#pragma once

enum class ActionState {
	NONE,
	PAINTING,
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
	ActionState actionState;
	ActionState previousActionState;
	ScreenState screenState;
private:
	Controller();
	~Controller();
public:
	static Controller* getInstance();

	// getters
	ActionState getActionState() const;
	ActionState getPreviousActionState() const;
	ScreenState getScreenState() const;
	bool isNone() const;
	bool isPainting() const;
	bool isEraseing() const;
	bool isBucketPainting() const;

	// setters
	void setActionState(ActionState actionState);
	void setScreenState(ScreenState screenState);
	void setPreviousActionState(ActionState previousActionState);
	void updatePreviousActionState();
};

