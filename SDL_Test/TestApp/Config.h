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

// main panel config
static const int MAIN_PANEL_WIDTH = SCREEN_WIDTH;
static const int MAIN_PANEL_HEIGHT = 2 * UNIT_HEIGHT;

static const int MAIN_PANEL_START_X = 0;
static const int MAIN_PANEL_START_Y = 0;

// color button config
static const int COLOR_BUTTON_NUMBER = 20;

static const int COLOR_BUTTON_WIDTH = 20;
static const int COLOR_BUTTON_HEIGHT = 20;

static const int COLOR_BUTTON_START_X = 25;
static const int COLOR_BUTTON_START_Y = 25;

static const int COLOR_BUTTON_OFFSET = COLOR_BUTTON_WIDTH + 5;

// color panel
static const int COLOR_PANEL_WIDTH = (COLOR_BUTTON_NUMBER / 2) * COLOR_BUTTON_WIDTH + (COLOR_BUTTON_NUMBER / 2 + 1) * 5;
static const int COLOR_PANEL_HEIGHT = COLOR_BUTTON_NUMBER * 2 + 15;

static const int COLOR_PANEL_START_X = 20;
static const int COLOR_PANEL_START_Y = 20;

// button confit
static const int PANEL_BUTTON_WIDTH = 64;
static const int PANEL_BUTTON_HEIGHT = 64;

static const int BUTTON_START_X = COLOR_PANEL_WIDTH + 3 * UNIT_WIDTH;
static const int BUTTON_START_Y = 25;

static const int BUTTON_SAPWN_DIFF_X = 2 * UNIT_WIDTH;
static const int BUTTON_SAPWN_DIFF_Y = UNIT_HEIGHT;

// texture config
static const std::string MINUS_BUTTON_PATH = "Assets/Textures/minus_button.png";
static const std::string PLUS_BUTTON_PATH = "Assets/Textures/plus_button.png";

// brush config
static const int BRUSH_INCREMENT = 1;