#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Button.h"

using namespace sf;

class mode
{
private:
	const int modeWith{ 1000 };
	const int modeHeight{ 800 };

	bool choice_mode = true;
	//true - single; false - multi

	bool input_box_access = true; //dostêp do input box

	std::string player1 = "Player1";
	Text player1Text;
	std::string player2 = "Player2";
	Text player2Text;

	Text name_input_box1;
	Text name_input_box2;

	RectangleShape shape1;
	RectangleShape shape2;

	RenderWindow windowMode;
	Font font;
	Text text;
public:
	mode(std::string text, int size);
	~mode();
	
	bool bool_mode();
	
	void setInputFilds();
	void setText(std::string text, int size);
	void setFont();
	String get_name();
	String get_name2();

};

