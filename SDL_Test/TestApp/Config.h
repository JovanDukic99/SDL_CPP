#pragma once
#include <string>

// screen config
static const std::string TITLE = "Game";
static const int SCREEN_WIDTH = 720;
static const int SCREEN_HEIGHT = 480;

// world config
static const int UNIT_WIDTH = 60;
static const int UNIT_HEIGHT = 60;

static const int VERTICAL_UNITS = SCREEN_WIDTH / UNIT_WIDTH;
static const int HORIZONTAL_UNITS = SCREEN_HEIGHT / UNIT_HEIGHT;

// player config
static const int PLAYER_WIDTH = UNIT_WIDTH;
static const int PLAYER_HEIGHT = UNIT_HEIGHT;

static const int START_PLAYER_X = 300;
static const int START_PLAYER_Y = 300;

static const int PLAYER_SPEEX_X = 10;
static const int PLAYER_SPEEX_Y = 10;

// camera config
static const int START_CAMERA_X = SCREEN_WIDTH / 2;
static const int START_CAMERA_Y = SCREEN_HEIGHT / 2;

// rubber config
static const int RUBBER_WIDTH = UNIT_WIDTH;
static const int RUBBER_HEIGHT = UNIT_HEIGHT;

// hud config
static const int PANEL_WIDTH = SCREEN_WIDTH;
static const int PANEL_HEIGHT = UNIT_HEIGHT;

static const int PANEL_X = 0;
static const int PANEL_Y = SCREEN_HEIGHT - UNIT_HEIGHT;

static const int BUTTON_NUMBER = 3;

static const int PANEL_BUTTON_WIDTH = UNIT_WIDTH;
static const int PANEL_BUTTON_HEIGHT = UNIT_HEIGHT;

static const int BUTTON_START_X = 3 * UNIT_WIDTH;
static const int BUTTON_START_Y = SCREEN_HEIGHT - UNIT_HEIGHT;

static const int BUTTON_SAPWN_DIFF_X = 2 * UNIT_WIDTH;
static const int BUTTON_SAPWN_DIFF_Y = UNIT_HEIGHT;