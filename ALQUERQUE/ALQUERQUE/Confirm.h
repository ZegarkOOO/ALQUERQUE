#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Button.h"

using namespace sf;

class Confirm
{
private:
	const int confirmWith{ 400 };
	const int confirmHeight{ 200 };

	RenderWindow windowConfirm;
	Font font;
	Text text;

	bool isConfirmBool; //ZMIENNA CZY POTWIERDZONO

public:
	Confirm(std::string text, int size);
	~Confirm();

	const bool isConfirm() const;

	void setText(std::string text, int size);
	void setFont();
};

