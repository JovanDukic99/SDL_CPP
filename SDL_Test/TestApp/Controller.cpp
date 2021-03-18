#include "Controller.h"

Controller* Controller::INSTANCE = nullptr;

Controller::Controller() : actionState(ActionState::NONE), screenState(ScreenState::REFRESH), previousActionState(ActionState::PAINTING) {

}

Controller::~Controller() {
    delete INSTANCE;
}

// getters
Controller* Controller::getInstance() {
    if (INSTANCE == nullptr) {
        INSTANCE = new Controller();
    }
    return INSTANCE;
}

ActionState Controller::getActionState() const {
    return actionState;
}

ActionState Controller::getPreviousActionState() const {
    return previousActionState;
}

ScreenState Controller::getScreenState() const {
    return screenState;
}

bool Controller::isNone() const {
    return actionState == ActionState::NONE;
}

bool Controller::isPainting() const {
    return actionState == ActionState::PAINTING;
}

bool Controller::isEraseing() const {
    return actionState == ActionState::ERASING;
}

bool Controller::isBucketPainting() const {
    return actionState == ActionState::BUCKET_PAINTING;
}

// setters
void Controller::setActionState(ActionState actionState) {
    this->actionState = actionState;
}

void Controller::updatePreviousActionState() {
    this->previousActionState = actionState;
}

void Controller::setScreenState(ScreenState screenState) {
    this->screenState = screenState;
}

void Controller::setPreviousActionState(ActionState previousActionState) {
    this->previousActionState = previousActionState;
}
