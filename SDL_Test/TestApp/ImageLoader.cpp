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
