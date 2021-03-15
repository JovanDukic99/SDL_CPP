#pragma once
#include <string>

// screen config
static const std::string TITLE = "Game";
static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 720;

// world config
static const int UNIT_WIDTH = 60;
static const int UNIT_HEIGHT = 60;

static const int VERTICAL_UNITS = SCREEN_WIDTH / UNIT_WIDTH;
static const int HORIZONTAL_UNITS = SCREEN_HEIGHT / UNIT_HEIGHT;

// rubber config
static const int RUBBER_WIDTH = UNIT_WIDTH;
static const int RUBBER_HEIGHT = UNIT_HEIGHT;

// hud config
static const int PANEL_WIDTH = SCREEN_WIDTH;
static const int PANEL_HEIGHT = 2 * UNIT_HEIGHT;

static const int PANEL_X = 0;
static const int PANEL_Y = 0;

static const int COLOR_BUTTON_NUMBER = 20;
static const int BUTTON_NUMBER = 4;

static const int COLOR_BUTTON_WIDTH = 20;
static const int COLOR_BUTTON_HEIGHT = 20;

static const int PANEL_BUTTON_WIDTH = 64;
static const int PANEL_BUTTON_HEIGHT = 64;

static const int BUTTON_START_X = 2 * UNIT_WIDTH;
static const int BUTTON_START_Y = 0;

static const int BUTTON_SAPWN_DIFF_X = 2 * UNIT_WIDTH;
static const int BUTTON_SAPWN_DIFF_Y = UNIT_HEIGHT;

// texture config
static const std::string TEST_IMAGE_PATH = "Assets/Textures/minus_button.png";