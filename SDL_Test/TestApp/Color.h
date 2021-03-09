#pragma once
#include <SDL/SDL.h>
#include <vector>

#define RED Color(255, 0, 0, 255)
#define GREEN Color(0, 255, 0, 255)
#define BLUE Color(0, 0, 255, 255)
#define YELLOW Color(255, 255, 0, 255)
#define WHITE Color(255, 255, 255, 255)
#define BLACK Color(0, 0, 0, 255)

class Color
{
private:
	std::vector<Uint8> coefficients;
public:
	// constructors;
	Color();
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	// init
	void init(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	// getters
	Uint8 getR();
	Uint8 getG();
	Uint8 getB();
	Uint8 getA();

	// setters
	void setR(Uint8 r);
	void setG(Uint8 g);
	void setB(Uint8 b);
	void setA(Uint8 a);

	// operator overload
	bool operator==(const Color& color);
};

