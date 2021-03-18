#include "Controller.h"

Controller* Controller::INSTANCE = nullptr;

Controller::Controller() : state(State::NONE), screenState(ScreenState::REFRESH) {

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

State Controller::getState() const {
    return state;
}

ScreenState Controller::getScreenState() const {
    return screenState;
}

// setters
void Controller::setState(State state) {
    this->state = state;
}

void Controller::setScreenState(ScreenState screenState) {
    this->screenState = screenState;
}
