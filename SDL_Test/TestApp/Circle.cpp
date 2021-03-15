#include "Circle.h"

Circle::Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {

}

int Circle::getX() {
	return x;
}

int Circle::getY() {
	return y;
}

int Circle::getRadius() {
	return radius;
}
