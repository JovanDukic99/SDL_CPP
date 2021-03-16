#include "ImageLoader.h"
#include <SDL_IMAGE/SDL_image.h>
#include <iostream>

SDL_Texture* ImageLoader::loadTexture(std::string filePath, SDL_Renderer* renderer) {
	SDL_Texture* texture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());

	if (loadedSurface == nullptr) {
		std::cout << "Failed to load the image." << std::endl;
		return nullptr;
	}

	texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

	if (texture == nullptr) {
		std::cout << "Failed to load the texture from image." << std::endl;
		return nullptr;
	}

	SDL_FreeSurface(loadedSurface);

	return texture;
}

SDL_Texture* ImageLoader::getTexture(std::string text, TTF_Font* font, SDL_Renderer* renderer) {
	SDL_Color colorFG{ 0, 0, 0, 255 };
	SDL_Surface* textSurface = nullptr;
	SDL_Texture* texture = nullptr;

	if ((textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), colorFG)) != nullptr) {
		if ((texture = SDL_CreateTextureFromSurface(renderer, textSurface)) == nullptr) {
			std::cout << "SDL_BlitSurface has failed." << std::endl;
		}
		SDL_FreeSurface(textSurface);
	}
	else {
		std::cout << "TTF_RenderText_Solid has failed." << std::endl;
	}

	return texture;
}
