#include "GUI.h"
#include "Config.h"
#include "Utils.h"
#include <iostream>

GUI::GUI() : gameState(GameState::PLAY), player(START_PLAYER_X, START_PLAYER_X, UNIT_WIDTH, UNIT_HEIGHT), shouldDrawRubber(false), numberOfInsertedBlocks(0) {
	init();
}

GUI::~GUI() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}

	if (font != nullptr) {
		TTF_CloseFont(font);
	}

	TTF_Quit();
	SDL_Quit();
}

void GUI::init() {
	initSDL();
	initTTF();
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

void GUI::initTTF() {
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init has failed." << std::endl;
	}
}

void GUI::initComponents() {
	// adjust rubber
	rubber.w = RUBBER_WIDTH;
	rubber.h = RUBBER_HEIGHT;

	// load fonts
	if ((font = TTF_OpenFont("fonts/Eastwood.ttf", 36)) == nullptr) {
		std::cout << "TTF_OpenFont has failed: " << TTF_GetError() << std::endl;
	}

	// set font attributes
	//TTF_SetFontStyle(font, TTF_STYLE_BOLD);

	int minx, maxx, miny, maxy, advance;
	if (TTF_GlyphMetrics(font, 'g', &minx, &maxx, &miny, &maxy, &advance) == -1)
		printf("%s\n", TTF_GetError());
	else {
		printf("minx    : %d\n", minx);
		printf("maxx    : %d\n", maxx);
		printf("miny    : %d\n", miny);
		printf("maxy    : %d\n", maxy);
		printf("advance : %d\n", advance);
	}
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
			inputManager.setMoving(true);
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
			if (event.button.button == SDL_BUTTON_LEFT) {
				blockNumber.push(numberOfInsertedBlocks);
				numberOfInsertedBlocks = 0;
			}
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
	/*else if (inputManager.isKeyPressed(SDLK_LCTRL) && inputManager.isKeyPressed(SDLK_z)) {
		if (blocks.empty()) {
			return;
		}

		int lastNumberOfBlocks = blockNumber.top();

		blocksErased.insert(blocksErased.begin() + blocksErased.size(), blocks.end() - lastNumberOfBlocks, blocks.end());
		blocks.erase(blocks.end() - lastNumberOfBlocks, blocks.end());

		blockNumber.pop();
		blockNumberErased.push(lastNumberOfBlocks);

		inputManager.releaseKey(SDLK_z);
		return;
	}
	else if (inputManager.isKeyPressed(SDLK_LCTRL) && inputManager.isKeyPressed(SDLK_y)) {
		if (blocksErased.empty()) {
			return;
		}

		int lastNumberOfBlocksErased = blockNumberErased.top();

		blocks.insert(blocks.begin() + blocks.size(), blocksErased.end() - lastNumberOfBlocksErased, blocksErased.end());
		blocksErased.erase(blocksErased.end() - lastNumberOfBlocksErased, blocksErased.end());

		blockNumberErased.pop();
		blockNumber.push(lastNumberOfBlocksErased);

		inputManager.releaseKey(SDLK_y);
		return;
	}*/
	
	player.update(inputManager);

	if (inputManager.isKeyPressed(SDL_BUTTON_LEFT) && inputManager.isMoving()) {
		hudPanel.update(inputManager);

		glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

		if (mouseCoords.y < hudPanel.getComponents()[0].getBounds()->y) {
			Button* button = hudPanel.getSelectedButton();

			if (button != nullptr) {
				int ID = button->getID();

				switch (ID)
				{
				case 0: {
					SDL_Rect rect;

					rect.w = UNIT_WIDTH / 10;
					rect.h = UNIT_HEIGHT / 10;

					int x = mouseCoords.x - rect.w / 2;
					int y = mouseCoords.y - rect.h / 2;

					rect.x = x;
					rect.y = y;

					blocks.emplace_back(rect, GREEN);
					numberOfInsertedBlocks += 1;
					break;
				}
				case 1: {
					int rectWidth = 4 * UNIT_WIDTH / 10;
					int rectHeight = rectWidth;

					int startX = mouseCoords.x - rectWidth / 2;
					int startY = mouseCoords.y - rectHeight / 2;

					int rowNumber = rectWidth / 6;
					int columnNumber = rowNumber;

					for (int i = 0; i < rowNumber; i++) {
						for (int j = 0; j < columnNumber; j++) {
							SDL_Rect rect;

							rect.w = UNIT_WIDTH / 10;
							rect.h = UNIT_HEIGHT / 10;

							rect.x = startX + j * rect.w;
							rect.y = startY + i * rect.h;

							blocks.emplace_back(rect, GREEN);
						}
					}

					numberOfInsertedBlocks += rowNumber * columnNumber;
					break;
				}
				case 2: {
					int startX = mouseCoords.x - UNIT_WIDTH / 2;
					int startY = mouseCoords.y - UNIT_HEIGHT / 2;

					int rowNumber = UNIT_WIDTH / 6;
					int columnNumber = rowNumber;

					for (int i = 0; i < rowNumber; i++) {
						for (int j = 0; j < columnNumber; j++) {
							SDL_Rect rect;

							rect.w = UNIT_WIDTH / 10;
							rect.h = UNIT_HEIGHT / 10;

							rect.x = startX + j * rect.w;
							rect.y = startY + i * rect.h;

							blocks.emplace_back(rect, GREEN);
						}
					}

					numberOfInsertedBlocks += rowNumber * columnNumber;
					break;
				}
				case 3: {
					drawCircle(mouseCoords.x, mouseCoords.y, 60);
					break;
				}
				default:
					SDL_Rect rect;

					rect.w = UNIT_WIDTH / 10;
					rect.h = UNIT_HEIGHT / 10;

					int x = mouseCoords.x - rect.w / 2;
					int y = mouseCoords.y - rect.h / 2;

					rect.x = x;
					rect.y = y;

					blocks.emplace_back(rect, GREEN);
					numberOfInsertedBlocks += 1;
					break;
				}

			}

		}

		inputManager.setMoving(false);
	}
	
	
	if (inputManager.isKeyPressed(SDL_BUTTON_RIGHT)) {
		glm::ivec2 mouseCoords = inputManager.getMouseCoordinates();

		rubber.x = mouseCoords.x - rubber.w / 2;
		rubber.y = mouseCoords.y - rubber.h / 2;

		for (size_t i = 0; i < blocks.size(); i++) {
			Block block = blocks[i];

			if (Utils::squareCollision(rubber, *block.getBounds())) {
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

	drawText();
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
	for (size_t i = 0; i < blocks.size(); i++) {
		Color color = blocks[i].getColor();
		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderFillRect(renderer, blocks[i].getBounds());
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

void GUI::drawCircle(int originX, int originY, int radius) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	int blocksAdded = 0;

	int x = 0;
	int y = radius;

	// decision parameter
	float p = 5/4 - radius;

	while (x <= y) {
		if (p < 0.0f) {
			x++;
			p += 2 * x + 2;
		}
		else {
			y--;
			x++;
			p += 2 * (x - y) + 1;
		}

		SDL_Rect rect;

		rect.w = 1;
		rect.h = 1;

		rect.x = originX + x;
		rect.y = originY + y;

		blocks.emplace_back(rect, GREEN);

		rect.x = originX + x;
		rect.y = originY - y;

		blocks.emplace_back(rect, GREEN);

		rect.x = originX - x;
		rect.y = originY + y;

		blocks.emplace_back(rect, GREEN);
		
		rect.x = originX - x;
		rect.y = originY - y;
		
		blocks.emplace_back(rect, GREEN);

		// ====================================//

		rect.x = originX - y;
		rect.y = originY + x;

		blocks.emplace_back(rect, GREEN);

		rect.x = originX + y;
		rect.y = originY - x;

		blocks.emplace_back(rect, GREEN);

		rect.x = originX - y;
		rect.y = originY - x;

		blocks.emplace_back(rect, GREEN);

		rect.x = originX + y;
		rect.y = originY + x;

		blocks.emplace_back(rect, GREEN);

		//SDL_RenderDrawPoint(renderer, originX + x, originY + y); // 1
		//SDL_RenderDrawPoint(renderer, originX + x, originY - y); // 4
		//SDL_RenderDrawPoint(renderer, originX - x, originY + y); // 8
		//SDL_RenderDrawPoint(renderer, originX - x, originY - y); // 5

		//SDL_RenderDrawPoint(renderer, originX - y, originY + x); // 7
		//SDL_RenderDrawPoint(renderer, originX + y, originY - x); // 3
		//SDL_RenderDrawPoint(renderer, originX - y, originY - x); // 6
		//SDL_RenderDrawPoint(renderer, originX + y, originY + x); // 2

		blocksAdded += 8;
	}

	numberOfInsertedBlocks += blocksAdded;
}

void GUI::drawText() {
	drawText("Block number: " + std::to_string(blocks.size()), 0, 0);
	drawText("Eastwood", 100, 100);
}

void GUI::drawText(std::string text, int x, int y) {
	SDL_Rect position;

	int xMin, xMax, yMin, yMax, advance;
	TTF_GlyphMetrics(font, 'g', &xMin, &xMax, &yMin, &yMax, &advance);

	int width = xMax - xMin;

	int textHeight = (yMax - yMin) + advance;
	int textWidth = advance * text.size();

	position.x = x;
	position.y = y;
	position.w = textWidth;
	position.h = textHeight;

	drawText(&position, text);
}

void GUI::drawText(SDL_Rect* position, std::string& text) {
	SDL_Color colorFG{ 255, 255, 255, 255 };
	SDL_Color colorBG{ 0, 0, 0, 255 };
	SDL_Surface* textSurface;
	SDL_Texture* texture;

	if ((textSurface = TTF_RenderUTF8_Shaded(font, text.c_str(), colorFG, colorBG)) != nullptr) {
		if ((texture = SDL_CreateTextureFromSurface(renderer, textSurface)) == nullptr) {
			std::cout << "SDL_BlitSurface has failed." << std::endl;
		}
		else {
			SDL_RenderCopy(renderer, texture, NULL, position);
		}
		SDL_FreeSurface(textSurface);
	}
	else {
		std::cout << "TTF_RenderText_Solid has failed." << std::endl;
	}

}
