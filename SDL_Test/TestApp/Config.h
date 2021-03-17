#pragma once
#include <string>

// screen config
static const std::string TITLE = "Game";
static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 720;

// color picker screen config
static const std::string COLOR_PICKER = "Color picker";
static const int COLOR_PICKER_WIDTH = 500;
static const int COLOR_PICKER_HEIGHT = 500;

// world config
static const int UNIT_WIDTH = 60;
static const int UNIT_HEIGHT = 60;

static const int VERTICAL_UNITS = SCREEN_WIDTH / UNIT_WIDTH;
static const int HORIZONTAL_UNITS = SCREEN_HEIGHT / UNIT_HEIGHT;

// rubber config
static const int RUBBER_WIDTH = 4 * UNIT_WIDTH;
static const int RUBBER_HEIGHT = 4 * UNIT_HEIGHT;

// main panel config
static const int MAIN_PANEL_WIDTH = SCREEN_WIDTH;
static const int MAIN_PANEL_HEIGHT = 2 * UNIT_HEIGHT;

static const int MAIN_PANEL_START_X = 0;
static const int MAIN_PANEL_START_Y = 0;

// color button config
static const int COLOR_BUTTON_NUMBER = 21;

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

// current color panel
static const int CURRENT_COLOR_PANEL_START_X = COLOR_PANEL_WIDTH + COLOR_BUTTON_OFFSET - 5;
static const int CURRENT_COLOR_PANEL_START_Y = COLOR_PANEL_START_Y + COLOR_BUTTON_OFFSET / 2;

static const int CURRENT_COLOR_PANEL_WIDTH = COLOR_BUTTON_OFFSET;
static const int CURRENT_COLOR_PANEL_HEIGHT = COLOR_BUTTON_OFFSET + 5;

// brush button confit
static const int PANEL_BUTTON_WIDTH = 64;
static const int PANEL_BUTTON_HEIGHT = 64;

static const int BUTTON_START_X = COLOR_PANEL_WIDTH + 3 * UNIT_WIDTH;
static const int BUTTON_START_Y = 25;

static const int BUTTON_SAPWN_DIFF_X = 2 * UNIT_WIDTH;
static const int BUTTON_SAPWN_DIFF_Y = UNIT_HEIGHT;

// asset config
static const std::string MINUS_BUTTON_PATH = "Assets/Textures/minus_button.png";
static const std::string PLUS_BUTTON_PATH = "Assets/Textures/plus_button.png";
static const std::string FONT_PATH = "fonts/Roboto-Light.ttf";

// color picker config
static const int COLOR_PICKER_COLOR_PANEL_WIDTH = 400;
static const int COLOR_PICKER_COLOR_PANEL_HEIGHT = 150;

static const int COLOR_PICKER_COLOR_PANEL_START_X = 50;
static const int COLOR_PICKER_COLOR_PANEL_START_Y = 50;

// color picker interval config
static const int COLOR_INTERVAL_HORIZONTAL_OFFSET = 50;

static const int COLOR_INTERVAL_START_X = 50;
static const int COLOR_INTERVAL_START_Y = COLOR_PICKER_COLOR_PANEL_START_Y + COLOR_PICKER_COLOR_PANEL_HEIGHT + COLOR_INTERVAL_HORIZONTAL_OFFSET;

static const int COLOR_INTERVAL_END_X = COLOR_INTERVAL_START_X + COLOR_PICKER_COLOR_PANEL_WIDTH;
static const int COLOR_INTERVAL_END_Y = COLOR_INTERVAL_START_Y;

static const int COLOR_INTERVAL_WIDTH = COLOR_INTERVAL_END_X - COLOR_INTERVAL_START_X;
static const int COLOR_RGB_MAX = 255;

// toogle button config
static const int TOGGLE_BUTTON_WIDTH = 5;
static const int TOGGLE_BUTTON_HEIGHT = 10;

// red toggle button config
static const int RED_TOGGLE_BUTTON_START_X = COLOR_INTERVAL_START_X;
static const int RED_TOGGLE_BUTTON_START_Y = COLOR_INTERVAL_START_Y;

// green toggle button config
static const int GREEN_TOGGLE_BUTTON_START_X = COLOR_INTERVAL_START_X;
static const int GREEN_TOGGLE_BUTTON_START_Y = COLOR_INTERVAL_START_Y + COLOR_INTERVAL_HORIZONTAL_OFFSET;

// blue toggle button config
static const int BLUE_TOGGLE_BUTTON_START_X = COLOR_INTERVAL_START_X;
static const int BLUE_TOGGLE_BUTTON_START_Y = COLOR_INTERVAL_START_Y + 2 * COLOR_INTERVAL_HORIZONTAL_OFFSET;

// label config
static const int LABEL_PADDING = 20;
static const int LABEL_OFFSET = 50;

static const int LABEL_START_X = (COLOR_INTERVAL_START_X + COLOR_INTERVAL_END_X) / 2;
static const int LABEL_START_Y = COLOR_INTERVAL_START_Y - LABEL_PADDING;

// submit button config
static const std::string SUBMIT_BUTTON = "Submit";

static const int SUBMIT_BUTTON_WIDTH = 100 + 10;
static const int SUBMIT_BUTTON_HEIGHT = 40 + 10;

static const int SUBMIT_BUTTON_START_X = (COLOR_PICKER_WIDTH - SUBMIT_BUTTON_WIDTH) / 2 - 5;
static const int SUBMIT_BUTTON_START_Y = COLOR_PICKER_HEIGHT - SUBMIT_BUTTON_HEIGHT - 20;

// brush label config
static const int BRUSH_LABEL_X = BUTTON_START_X + PANEL_BUTTON_WIDTH + UNIT_WIDTH / 2 - 2;
static const int BRUSH_LABEL_Y = BUTTON_START_Y + PANEL_BUTTON_HEIGHT / 2;

// brush config
static const int BRUSH_INCREMENT = 1;