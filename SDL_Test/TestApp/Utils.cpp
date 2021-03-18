#include "Utils.h"
#include "ImageLoader.h"
#include "Config.h"

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

int Utils::calculateRGBValueFromPositon(int x, int A, int B, int C) {
    return ((x - A) / (float)B) * C;
}

int Utils::calculatePositionFromRGBValue(int A, int B, int C, int D) {
    return (D * B / (float) C) + A;
}

SDL_Cursor* Utils::getCursor(ActionState state) {
    switch (state)
    {
    case ActionState::NONE: {
        return SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    }
    case ActionState::PAINTING: {
        return SDL_CreateColorCursor(ImageLoader::loadCursorSurface(PENCIL_CURSOR_PATH), PENCIL_CURSOR_HOT_X, PENCIL_CURSOR_HOT_Y);
    }
    case ActionState::ERASING: {
        return SDL_CreateColorCursor(ImageLoader::loadCursorSurface(RUBBER_CURSOR_PATH), RUBBER_CURSOR_HOT_X, RUBBER_CURSOR_HOT_Y);
    }
    case ActionState::BUCKET_PAINTING: {
        return SDL_CreateColorCursor(ImageLoader::loadCursorSurface(BUCKET_CURSOR_PATH), BUCKET_CURSOR_HOT_X, BUCKET_CURSOR_HOT_Y);
    }
    default:
        return SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    }
}

std::vector<SDL_Rect> Utils::getLinePath(glm::ivec2 p1, glm::ivec2 p2, int pathWidth, int pathHeight) {
    std::vector<SDL_Rect> path;
    std::vector<glm::ivec2> points;

    /*int dx = std::abs(p2.x - p1.x);
    int dy = std::abs(p2.y - p1.y);
    int N = std::max(dx, dy);

    float divN = ((N == 0) ? 0.0f : (1.0f / N));
    float xStep = dx * divN;
    float yStep = dy * divN;

    float x = p1.x;
    float y = p1.y;

    path.reserve(N + 1);
    points.reserve(N + 1);

    for (int step = 0; step <= N; step++, x += xStep, y += yStep) {
        points.push_back(glm::ivec2(std::round(x), std::round(y)));
    }*/

    glm::fvec2 start = p1;
    glm::fvec2 end = p2;

    float N = glm::distance(start, end);

    path.reserve(N + 1);
    path.reserve(N + 1);

    for (int step = 0; step <= N; step++) {
        float t = ((N == 0) ? 0.0f : (step / N));
        points.push_back(glm::round(lerp(start, end, t)));
    }

    for (size_t i = 0; i < points.size(); i++) {
        SDL_Rect rect;
        glm::ivec2 point = points[i];

        rect.w = pathWidth;
        rect.h = pathHeight;

        rect.x = point.x - pathWidth / 2;
        rect.y = point.y - pathHeight / 2;
        
        path.push_back(rect);
    }

    return path;
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

glm::fvec2 Utils::lerp(glm::fvec2 p1, glm::fvec2 p2, float t) {
    return p1 * (1 - t) + p2 * t;
}
