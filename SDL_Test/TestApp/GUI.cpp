#include "GUI.h"
#include "Config.h"
#include "Utils.h"
#include <iostream>

GUI::GUI() : gameState(GameState::PLAY), player(START_PLAYER_X, START_PLAYER_X, UNIT_WIDTH, UNIT_HEIGHT), shouldDrawRubber(false) {
	init();
}

GUI::~GUI() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	
	SDL_Quit();
}

void GUI::init() {
	initSDL();
	initComponents();
	run();
}

void GUI::initSDL() {
	// init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Could not initialize SDL." << std::endl;
		return;
	}

	// init window
	window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "Could not initialize SDL_Window." << std::endl;
		return;
	}

	// init surface
	if ((surface = SDL_GetWindowSurface(window)) == nullptr) {
		std::cout << "Could not initialize SDL_Surface." << std::endl;
		return;
	}

	// init renderer
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC)) == nullptr) {
		std::cout << "Could not initialize SDL_Renderer." << std::endl;
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return;
	}
}

void GUI::initComponents() {
	rubber.w = RUBBER_WIDTH;
	rubber.h = RUBBER_HEIGHT;
}

void GUI::run() {
	while (gameState != GameState::EXIT) {
		handleInputEvents();
		update();
		draw();
	}
}

void GUI::handleInputEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT: {
			gameState = GameState::EXIT;
			break;
		}
		case SDL_MOUSEMOTION: {
			inputManager.setMouseCoordinates(event.motion.x, event.motion.y);
			break;
		}
		case SDL_KEYDOWN: {
			inputManager.pressKey(event.key.keysym.sym);
			break;
		}
		case SDL_KEYUP: {
			inputManager.releaseKey(event.key.keysym.sym);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			inputManager.pressKey(event.button.button);
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			inputManager.releaseKey(event.button.button);
			break;
		}
		default:
			break;
		}
	}
}

void GUI::update() {
	if (inputManager.isKeyPressed(SDLK_ESCAPE)) {
		gameState = GameState::EXIT;
		return;	
	}
	
	player.update(inputManager);

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
		hudPanel.update(inputManager);

		glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();
		Button* button = hudPanel.getSelectedButton();
		SDL_Rect rect;

		if (button != nullptr) {
			int ID = button->getID();

			switch (ID)
			{
			case 0: {
				rect.w = UNIT_WIDTH * 0.1f;
				rect.h = UNIT_HEIGHT * 0.1f;

				int x = mouseCoords.x - rect.w / 2;
				int y = mouseCoords.y - rect.h / 2;

				rect.x = x;
				rect.y = y;

				blocks.push_back(rect);

				break;
			}
			case 1: {
				rect.w = 4 * UNIT_WIDTH / 10;
				rect.h = 4 *UNIT_HEIGHT / 10;
				break;
			}
			case 2: {
				rect.w = 8 * UNIT_WIDTH / 10;
				rect.h = 8 *UNIT_HEIGHT / 10;

				int startX = mouseCoords.x - UNIT_WIDTH * 0.1f / 2;
				int startY = mouseCoords.y - UNIT_HEIGHT * 0.1f / 2;

				rect.x = x;
				rect.y = y;

				blocks.push_back(rect);

				break;
			}
			default:
				rect.w = UNIT_WIDTH / 10;
				rect.h = UNIT_HEIGHT / 10;

				int x = mouseCoords.x - UNIT_WIDTH * 0.1f / 2;
				int y = mouseCoords.y - UNIT_HEIGHT * 0.1f / 2;

				rect.x = x;
				rect.y = y;

				blocks.push_back(rect);

				break;
			}

		}

	}
	
	
	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

		rubber.x = mouseCoords.x - rubber.w / 2;
		rubber.y = mouseCoords.y - rubber.h / 2;

		for (size_t i = 0; i < blocks.size(); i++) {
			if (Utils::squareCollision(rubber, blocks[i])) {
				blocks.erase(blocks.begin() + i);
			}
		}

		shouldDrawRubber = true;
	}
	else {
		shouldDrawRubber = false;
	}

}

void GUI::draw() {
	// clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, nullptr);

	drawGrid();
	drawBlocks();
	drawPlayer();
	drawRubber();
	drawHUD();

	// update SDL window
	SDL_RenderPresent(renderer);
}

void GUI::drawGrid() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// draw vertical lines
	for (size_t i = 0; i < VERTICAL_UNITS; i++) {
		SDL_RenderDrawLine(renderer, i * UNIT_WIDTH, 0, i * UNIT_WIDTH, SCREEN_HEIGHT);
	}

	// draw horizontal line
	for (size_t i = 0; i < HORIZONTAL_UNITS; i++) {
		SDL_RenderDrawLine(renderer, 0, i * UNIT_HEIGHT, SCREEN_WIDTH, i * UNIT_HEIGHT);
	}
}

void GUI::drawPlayer() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, player.getBounds());
}

void GUI::drawBlocks() {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	for (size_t i = 0; i < blocks.size(); i++) {
		SDL_RenderFillRect(renderer, &blocks[i]);
	}
}

void GUI::drawRubber() {
	if (shouldDrawRubber) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &rubber);
	}
}

void GUI::drawHUD() {
	std::vector<HudBase> components = hudPanel.getComponents();
	for (size_t i = 0; i < components.size(); i++) {
		HudBase base = components[i];
		Color color = base.getColor();

		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderFillRect(renderer, base.getBounds());
	}
}
