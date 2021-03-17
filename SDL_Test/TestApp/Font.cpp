#include "Font.h"
#include "ImageLoader.h"
#include <iostream>

Font::Font() : font(nullptr) {

}

Font::Font(std::string fontPath, int size) {
	init(fontPath, size);
}

// init
void Font::init(std::string fontPath, int size) {
	loadFont(fontPath, size);
}

void Font::loadFont(std::string fontPath, int size) {
	if ((font = TTF_OpenFont(fontPath.c_str(), size)) == nullptr) {
		std::cout << "Failed to load font: " << fontPath << std::endl;
	}
}

// getters
SDL_Texture* Font::getTexture(std::string text, SDL_Renderer* renderer) {
	return ImageLoader::getTexture(text, font, renderer);
}

SDL_Rect Font::getTextBounds(std::string text, int x, int y) {
	SDL_Rect bounds;

	const char* chars = text.c_str();

	int width = 0, maxHeight = INT_MAX;
	int minx, maxx, miny, maxy, advance, glyphHeight;

	for (size_t i = 0; i < text.size(); i++) {
		if (TTF_GlyphMetrics(font, chars[i], &minx, &maxx, &miny, &maxy, &advance) == -1) {
			std::cout << "There is no glyph metrics for char: " << chars[i] << std::endl;
			continue;
		}

		width += maxx - minx;
		glyphHeight = maxy - miny;

		if (glyphHeight < maxHeight) {
			maxHeight = glyphHeight;
		}
	}

	bounds.x = x - width / 2;
	bounds.y = y - maxHeight / 2;
	bounds.w = width;
	bounds.h = maxHeight;

	return bounds;
}

void Font::setFont(TTF_Font*& font) {
	this->font = font;
}
