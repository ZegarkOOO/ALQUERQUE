#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

//STANY PRZYCISKU
enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button
{
private:
	short unsigned buttonState;
	RectangleShape shape;
	Font font;
	Text text;

	Color idle_color; // kolor bezczynnosci
	Color hover_color; // kolor najechania
	Color active_color; // kolor aktywacji

public:
	Button(float x, float y, float width, float height, int size, std::string text, 
				Color idle_color, Color hover_color, Color active_color);
	~Button();
	const bool isPressed() const;
	void update(const Vector2f mousePos);
	void render(RenderWindow* target);
	void setFont();
};

