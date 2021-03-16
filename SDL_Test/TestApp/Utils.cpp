#include "Utils.h"

bool Utils::squareCollision(SDL_Rect r1, SDL_Rect r2) {
    return areColliding(r1, r2) || areColliding(r2, r1);
}

bool Utils::areColliding(SDL_Rect r1, SDL_Rect r2) {
    if (r1.x + r1.w < r2.x) {
        return false;
    }
    else if (r2.x + r2.w < r1.x) {
        return false;
    }
    else if (r1.y < r2.y) {
        return false;
    }
    else if (r2.y + r2.h < r1.y) {
        return false;
    }

    return true;
}

bool Utils::isPointInsideBounds(glm::ivec2 mouseCoords, SDL_Rect bounds) {
    if (mouseCoords.x >= bounds.x && mouseCoords.x <= bounds.x + bounds.w) {
        if (mouseCoords.y >= bounds.y && mouseCoords.y <= bounds.y + bounds.h) {
            return true;
        }
    }
    return false;
}

Color Utils::getButtonColor(int index) {
    switch (index)
    {
    case 0:
        return RED;
    case 1:
        return GREEN;
    case 2:
        return BLUE;
    case 3:
        return YELLOW;
    case 4:
        return WHITE;
    case 5:
        return BLACK;
    case 6:
        return BYZANTINE;
    case 7:
        return SEA_GREEN;
    case 8:
        return TRUE_BLUE;
    case 9:
        return SKY_MAGENTA;
    case 10:
        return LEMON_GLACIER;
    case 11:
        return CITRON;
    case 12:
        return MARIGOLD;
    case 13:
        return BRICK_RED;
    case 14:
        return DARK_CORNFLOWER_BLUE;
    case 15:
        return LIME_GREEN;
    case 16:
        return FOREST_GREEN_WEB;
    case 17:
        return ZOMP;
    case 18:
        return LIGHT_STEEL_BLUE;
    case 19:
        return YELLOW_GREEN;
    default:
        return BLACK;
    }
    return Color();
}
