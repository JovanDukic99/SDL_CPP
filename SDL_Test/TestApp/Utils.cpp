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
