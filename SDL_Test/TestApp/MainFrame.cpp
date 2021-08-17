#include "MainFrame.h"
#include "Config.h"
#include "Component.h"
#include "Utils.h"
#include "ImageLoader.h"
#include <iostream>

#define DESIRED_FPS 60
#define MILISECONDS 1000
#define DESIRED_FRAME_TIME (MILISECONDS / DESIRED_FPS)

MainFrame::MainFrame() : gameState(GameState::PLAY) {
	init();
}

MainFrame::~MainFrame() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	}

	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}

	TTF_Quit();
	SDL_Quit();
}

void MainFrame::init() {
	initSDL();
	initTTF();
	initFont();
	initSDL_Image();
	initController();
	initFont();
	initComponents();
	initDraw();
	run();
}

void MainFrame::initSDL() {
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

	// init renderer
	if ((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC)) == nullptr) {
		std::cout << "Could not initialize SDL_Renderer." << std::endl;
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return;
	}
}

void MainFrame::initTTF() {
	if (TTF_Init() == -1) {
		std::cout << "TTF_Init has failed." << std::endl;
		return;
	}
}

void MainFrame::initSDL_Image() {
	int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags)) {
		std::cout << "Could not initialize SDL_Image." << std::endl;
		return;
	}
}

void MainFrame::initController() {
	controller = Controller::getInstance();
	inputManager = controller->getInputManager();
}

void MainFrame::initComponents() {
	// adjust rubber
	rubber.w = RUBBER_WIDTH;
	rubber.h = RUBBER_HEIGHT;

	// forward the renderer to mainPanel
	mainPanel.setFont(font);
	mainPanel.setRenderer(renderer);
	mainPanel.init();

	// forward the renderer to chatPanel
	chatPanel.setRenderer(renderer);

	// forward font to ColorPicker
	colorPicker.setFont(font);
}

void MainFrame::initFont() {
	font.init(FONT_PATH, 32);
}

void MainFrame::run() {
	while (gameState != GameState::EXIT) {
		Uint32 startTime = SDL_GetTicks();
		handleInputEvents();
		update();
		updateScreen();
		reset();

		Uint32 endTime = SDL_GetTicks();
		Uint32 frameTime = endTime - startTime;

		if (DESIRED_FRAME_TIME > frameTime) {
			SDL_Delay(DESIRED_FRAME_TIME - frameTime);
			start = inputManager->getMouseCoordinates();
		}
	}
}

void MainFrame::handleInputEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT: {
			gameState = GameState::EXIT;
			break;
		}
		case SDL_WINDOWEVENT: {
			handleWindowEvents(event);
			break;
		}
		case SDL_MOUSEMOTION: {
			inputManager->setMoving(true);
			inputManager->setMouseCoordinates(event.motion.x, event.motion.y);
			inputManager->setWindowID(event.window.windowID);
			break;
		}
		case SDL_TEXTINPUT: {
			inputManager->setTextInput(event.text.text, true);
			break;
		}
		case SDL_KEYDOWN: {
			inputManager->pressKey(event.key.keysym.sym);
			break;
		}
		case SDL_KEYUP: {
			inputManager->releaseKey(event.key.keysym.sym);
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			inputManager->pressKey(event.button.button);
			inputManager->setClickNumber(event.button.clicks);
			inputManager->setWindowID(event.window.windowID);
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			inputManager->releaseKey(event.button.button);
			inputManager->setWindowID(event.window.windowID);
			break;
		}
		default:
			break;
		}
	}
}

void MainFrame::handleWindowEvents(SDL_Event& event) {
	switch (event.window.event)
	{
	case SDL_WINDOWEVENT_CLOSE: {
		if (event.window.windowID != SDL_GetWindowID(window)) {
			controller->setMode(controller->getPreviousActionState());
			updateCursor();
			colorPicker.closeWindow();
		}
		break;
	}
	default:
		break;
	}
}

void MainFrame::update() {
	glm::ivec2 mouseCoords = inputManager->getMouseCoordinates();

	if (inputManager->isKeyPressed(SDLK_ESCAPE)) {
		gameState = GameState::EXIT;
		return;	
	}

	// update start position
	if (!inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
		start = mouseCoords;
	}

		// should open colorPicker
		if (!colorPicker.isVisible() && mainPanel.openColorPicker()) {
			colorPicker.init(mainPanel.getSelectedColor());
			controller->setMode(Mode::NONE);
			updateCursor();
			return;
		}

		// update colorPicker
		if (updateColorPicker()) {
			return;
		}

		// end writing
		if (textArea != nullptr && controller->isWriting() && (mouseCoords.y < MAIN_PANEL_HEIGHT || mouseCoords.x > CHAT_PANEL_START_X)) {
			controller->updatePreviousMode();
			controller->setMode(Mode::NONE);
			refresh();
			updateCursor();
			resetTextArea();
			return;
		}

		// save previous state and switch to hand cursor (mainPanel)
		if (!controller->isNone() && mouseCoords.y < MAIN_PANEL_HEIGHT ) {
			controller->updatePreviousMode();
			controller->setMode(Mode::NONE);
			refresh();
			updateCursor();
			return;
		}

		// save previous state and switch to hand cursor (chatPanel)
		if (!controller->isNone() && mouseCoords.x > CHAT_PANEL_START_X && mouseCoords.y > CHAT_PANEL_START_Y) {
			controller->updatePreviousMode();
			controller->setMode(Mode::NONE);
			refresh();
			updateCursor();
			return;
		}

		if (controller->isNone() && mouseCoords.x > CHAT_PANEL_START_X && mouseCoords.y > CHAT_PANEL_START_Y) {
			
			return;
		}

		// check if update happened in mainPanel
		if (controller->isNone() && inputManager->isKeyPressed(SDL_BUTTON_LEFT)) {
			if (mainPanel.update()) {
				refresh();
				drawHUD();
				inputManager->releaseKey(SDL_BUTTON_LEFT);
				return;
			}
		}

		// switch to previous state
		if (controller->isNone() && mouseCoords.y >= MAIN_PANEL_HEIGHT) {
			controller->setMode(controller->getPreviousActionState());
			controller->setScreenState(ScreenState::REFRESH);
			updateCursor();
			return;
		}

		// wiritng
		if (controller->isWriting() && inputManager->isKeyPressed(SDL_BUTTON_LEFT) && textArea == nullptr) {
			textArea = new TextArea(mouseCoords, BLACK, font, renderer);
			inputManager->releaseKey(SDL_BUTTON_LEFT);
			return;
		}
		else if (controller->isWriting() && inputManager->isKeyPressed(SDL_BUTTON_LEFT) && textArea != nullptr) {
			refresh();
			resetTextArea();
			inputManager->releaseKey(SDL_BUTTON_LEFT);
			return;
		}
		else if (controller->isWriting() && textArea != nullptr) {
			textArea->update(DESIRED_FRAME_TIME);
			textArea->draw();
			refresh();
			return;
		}
		else if (!controller->isWriting() && textArea != nullptr) {
			refresh();
			resetTextArea();
			return;
		}

		// erasing
		if (inputManager->isKeyPressed(SDL_BUTTON_LEFT) && controller->isEraseing() && inputManager->isMoving()) {
			refresh();

			glm::ivec2 mouseCoords = inputManager->getMouseCoordinates();

			rubber.x = mouseCoords.x - RUBBER_CURSOR_HOT_X;
			rubber.y = mouseCoords.y - RUBBER_CURSOR_HOT_Y;

			end = mouseCoords;

			std::vector<SDL_Rect> path = Utils::getLinePath(start, end, RUBBER_WIDTH, RUBBER_HEIGHT);

			for (size_t i = 0; i < path.size(); i++) {
				SDL_Rect bounds = path[i];

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(renderer, &bounds);
			}

			start = end;

			return;
		}
		
		// bucket painting
		if (inputManager->isKeyPressed(SDL_BUTTON_LEFT) && controller->isBucketPainting()) {
			Utils::paintWithBucket(mouseCoords, mainPanel.getSelectedColor(), renderer);
			refresh();
			inputManager->releaseKey(SDL_BUTTON_LEFT);
			return;
		}

		// painting
		if (inputManager->isKeyPressed(SDL_BUTTON_LEFT) && controller->isPainting() && inputManager->isMoving()) {
			refresh();

			if (mouseCoords.y > MAIN_PANEL_HEIGHT) {
				if (controller->isPainting()) {
					int brushSize = mainPanel.getBrushSize();
					Color color = mainPanel.getSelectedColor();

					int width = brushSize * UNIT_WIDTH / 20;
					int height = brushSize * UNIT_WIDTH / 20;

					int x = mouseCoords.x - width / 2;
					int y = mouseCoords.y - height / 2;

					end = mouseCoords;

					std::vector<SDL_Rect> path = Utils::getLinePath(start, end, width, height);

					for (size_t i = 0; i < path.size(); i++) {
						SDL_Rect bounds = path[i];

						SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
						SDL_RenderFillRect(renderer, &bounds);
					}

					inputManager->setMoving(false);

					start = end;
				}
			}
		}
}

bool MainFrame::updateColorPicker() {
	if (colorPicker.isVisible()) {
		colorPicker.update();
		if (!colorPicker.isVisible()) {
			mainPanel.setSelectedColor(colorPicker.getColor());
			colorPicker.closeWindow();
			controller->setScreenState(ScreenState::REFRESH);
			drawHUD();
		}
		return true;
	}
	return false;
}

void MainFrame::initDraw() {
	// draw background color
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, nullptr);

	// draw hud
	drawHUD();

	// draw chatPanel
	drawChatPanel();

	updateScreen();
}

void MainFrame::drawHUD() {
	// draw panels
	std::vector<Component> panels = mainPanel.getPanels();
	for (size_t i = 0; i < panels.size(); i++) {
		SDL_Rect bounds = panels[i].getBounds();
		Color color = panels[i].getColor();

		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderFillRect(renderer, &bounds);
	}

	// draw color buttons
	std::vector<Component> colorButtons= mainPanel.getColorButtons();
	for (size_t i = 0; i < colorButtons.size(); i++) {
		SDL_Rect bounds = colorButtons[i].getBounds();
		Color color = colorButtons[i].getColor();

		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderFillRect(renderer, &bounds);
	}

	// draw utility buttons
	std::vector<Component> utlilityButtons = mainPanel.getUtilityButtons();
	for (size_t i = 0; i < utlilityButtons.size(); i++) {
		SDL_Rect bounds = utlilityButtons[i].getBounds();
		Color color = utlilityButtons[i].getColor();
		SDL_Texture* texture = utlilityButtons[i].getTexture();

		SDL_RenderCopy(renderer, texture, NULL, &bounds);
		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderDrawRect(renderer, &bounds);
	}

	// draw brush buttons
	std::vector<Component> brushButtons = mainPanel.getBrushButtons();
	for (size_t i = 0; i < brushButtons.size(); i++) {
		SDL_Rect bounds = brushButtons[i].getBounds();
		Color color = brushButtons[i].getColor();
		SDL_Texture* texture = brushButtons[i].getTexture();

		SDL_RenderCopy(renderer, texture, NULL, &bounds);
		SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
		SDL_RenderDrawRect(renderer, &bounds);
	}

	// draw brush label
	std::string brushLabel = std::to_string(mainPanel.getBrushSize());
	SDL_Texture* texture = nullptr;
	SDL_Rect labelBounds;
	font.obtainTextData(brushLabel, BLACK, renderer, &texture, &labelBounds, glm::ivec2(BRUSH_LABEL_X, BRUSH_LABEL_Y));

	SDL_RenderCopy(renderer, texture, NULL, &labelBounds);
}

void MainFrame::drawChatPanel() {
	chatPanel.draw();
}

void MainFrame::updateCursor() {
	SDL_SetCursor(Utils::getCursor(controller->getActionState()));
}

void MainFrame::drawCircle(int originX, int originY, int radius) {
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

		rect.w = 3;
		rect.h = 3;

		rect.x = originX + x;
		rect.y = originY + y;

		SDL_RenderFillRect(renderer, &rect);

		rect.x = originX + x;
		rect.y = originY - y;

		SDL_RenderFillRect(renderer, &rect);

		rect.x = originX - x;
		rect.y = originY + y;

		SDL_RenderFillRect(renderer, &rect);
		
		rect.x = originX - x;
		rect.y = originY - y;
		
		SDL_RenderFillRect(renderer, &rect);

		// ====================================//

		rect.x = originX - y;
		rect.y = originY + x;

		SDL_RenderFillRect(renderer, &rect);

		rect.x = originX + y;
		rect.y = originY - x;

		SDL_RenderFillRect(renderer, &rect);

		rect.x = originX - y;
		rect.y = originY - x;

		SDL_RenderFillRect(renderer, &rect);

		rect.x = originX + y;
		rect.y = originY + x;

		SDL_RenderFillRect(renderer, &rect);
	}
}

void MainFrame::updateScreen() {
	if (doRefresh()) {
		SDL_RenderPresent(renderer);
		freeze();
	}
}

bool MainFrame::doRefresh() {
	return controller->getScreenState() == ScreenState::REFRESH;
}

void MainFrame::refresh() {
	controller->setScreenState(ScreenState::REFRESH);
}

void MainFrame::freeze() {
	controller->setScreenState(ScreenState::FREEZE);
}

void MainFrame::resetTextArea() {
	delete textArea;
	textArea = nullptr;
}

void MainFrame::reset() {
	inputManager->setClickNumber(0);
	inputManager->setTextInput(nullptr, false);
}
