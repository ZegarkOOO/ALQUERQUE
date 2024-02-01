#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h"
#include "Menu.h"

using namespace sf;

class TheEnd
{
private:
	const int windowWith{ 1000 };
	const int windowHeight{ 800 };

	RenderWindow window;

	Text napis, winner, ctime, cmove, labeltime, labelmove;
	Font font;



public:
	TheEnd(String winner, int countmove, int counttime); 
	void setFont();
	

};

