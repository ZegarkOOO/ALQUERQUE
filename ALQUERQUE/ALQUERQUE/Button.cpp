#include "Button.h"

/*KONSTRUKTOR Z ARGUMENTAMI*/
Button::Button(float x, float y, float width, float height, int size, std::string text,
	Color idle_color, Color hover_color, Color active_color)
{
	//USTAWNIENIE WSZYSTKICH POTRZEBNYCH ATRYBUTÓW PRZYCISKU
	this->buttonState = BTN_IDLE;
	this->shape.setPosition(Vector2f(x, y));
	this->shape.setSize(Vector2f(width, height));
	this->setFont();
	this->text.setFont(this->font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(size);
	this->text.setString(text);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - 1.5f * this->text.getGlobalBounds().height / 2.f
	);
	this->idle_color = idle_color;
	this->hover_color = hover_color;
	this->active_color = active_color;
	this->shape.setFillColor(this->idle_color);

}

/*DESTRUKTOR*/
Button::~Button() {
}

/*ZWRACA CZY PRZYCISK PRZYCISNIÊTY*/
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_PRESSED) {
		return true;
	}
	return false;
}


/*AKTUALIZOWANIE PRZYCISKU*/
void Button::update(const Vector2f mousePos)
{
	/*Update the bool states*/

	//Idle
	this->buttonState = BTN_IDLE;
	//std::cout << "nie na przycisku\n";

	//Hover
	if(this->shape.getGlobalBounds().contains(mousePos)){
		this->buttonState = BTN_HOVER;

		//Pressed
		if (Mouse::isButtonPressed(Mouse::Left)) {
			this->buttonState = BTN_PRESSED;
		}
	}

	//ZMIANA KOLORU WZGLÊDEM STANU
	switch (this->buttonState) 
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idle_color);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hover_color);
		break;

	case BTN_PRESSED:
		this->shape.setFillColor(this->active_color);
		break;

	default:
		this->shape.setFillColor(Color::Red);
		break;
	}
}

/*RENDEROWANIE*/
void Button::render(RenderWindow* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

/*£ADOWANIE CZCIONKI*/
void Button::setFont()
{ 
	if (!this->font.loadFromFile("Tealand.ttf")) {
		std::cout << "font file is broken!\n";
	}
}
