#include "Pawn.h"

/*KONSTRUKTOR DOMYŒLNY*/
Pawn::Pawn()
{
}

/*KONSTRUKTOR Z PARAMETRAMI*/
Pawn::Pawn(int number, Color color)
{
	this->pawn_number = number;
	this->pawn_color = color;
	this->pawn_shape.setRadius(this->pawn_radius);
	this->pawn_shape.setPosition(this->pawn_position);
	this->pawn_shape.setFillColor(this->pawn_color);
	this->pawn_shape.setOrigin(this->pawn_radius, this->pawn_radius);
}

/*KONSTRUKTOR Z WIÊKSZ¥ ILOŒCI¥ ARGUMENTÓW*/
Pawn::Pawn(int number, Color color, float x, float y, float radius)
{
	this->pawn_number = number;
	this->pawn_color = color;
	this->pawn_radius = radius;
	this->pawn_shape.setRadius(this->pawn_radius);
	this->pawn_shape.setPosition(x, y);
	this->pawn_shape.setFillColor(this->pawn_color);
	this->pawn_shape.setOrigin(this->pawn_radius, this->pawn_radius);
}

/*DESTRUKTOR*/
Pawn::~Pawn()
{
	//std::cout << "Zniszczono piona\n";
}

/*USTAWIENIE POZYCJI PIONA*/
void Pawn::setPawnPositionArray(int x, int y)
{
	this->pawn_position_array.x = x;
	this->pawn_position_array.y = y;
}

/*ZWRACA INDEKSY W TABLICY ZAJÊTOŒCI*/
Vector2i Pawn::getPawnPositionArray()
{
	return this->pawn_position_array;
}

/*USTAWIENIE POZYCJI PIONA 2*/
void Pawn::setPawnPosition(float pos_x, float pos_y)
{
	this->pawn_position.x = pos_x;
	this->pawn_position.y = pos_y;
	this->pawn_shape.setPosition(this->pawn_position.x, this->pawn_position.y);
}

/*NADPISANIE OPERATORA = */
Pawn& Pawn::operator=(Pawn pion)
{
	this->pawn_number = pion.pawn_number;
	this->pawn_color = pion.pawn_color;
	this->pawn_position = pion.pawn_position;
	this->pawn_radius = pion.pawn_radius;
	this->pawn_shape = pion.pawn_shape;
	this->pawn_position_array = pion.pawn_position_array;
	return *this;
}

/*RENDER PIONA - RYSOWANIE*/
void Pawn::render(RenderTarget* target)
{
	if (this->get_live()) {
		target->draw(this->pawn_shape);
	}
}

/*AKTUALIZACJA PIONA */
bool Pawn::update(const Vector2f mousePos, std::vector < Vector2i >& available_position, int& selected)
{
	if (this->pawn_shape.getGlobalBounds().contains(mousePos) && this->get_live() == true) {
		if (Mouse::isButtonPressed(Mouse::Left)) {

			//USTAWNIENIE TEGO PIONA NA WYBRANEGO
			selected = this->getPawn_number();
			if (this->getPawn_color() == Color::Green) {
				this->pawn_shape.setFillColor(Color(25, 80, 35, 255));
			}
			else {
				this->pawn_shape.setFillColor(Color(200, 0, 0, 255));
			}
		}
	}
	//POWRÓT DO DEFAULTOWEGO KOLORU
	if (Mouse::isButtonPressed(Mouse::Right)) {
		this->pawn_shape.setFillColor(this->pawn_color);
	}
	return false;
}

/*FUNKCJA U¯YWANA DO WYBRANIA RUCHU*/
bool Pawn::update_move(const Vector2f mousePos, Vector2i &move)
{
	if (this->pawn_shape.getGlobalBounds().contains(mousePos)) {
		if (Mouse::isButtonPressed(Mouse::Left)) {

			//ZWRACA INDEKSY Z TABLICY ZAJÊTOŒCI
			move = this->pawn_position_array;
			return true;
		}
	}
	else {
		return false;
	}
}

/*USTAWIENIE POZYCJI PIONKA*/
void Pawn::setPawnPosition(Vector2f vector_pos)
{
	this->pawn_position = vector_pos;
	this->pawn_shape.setPosition(this->pawn_position);
}

/*ZWRACA NUMER PIONKA*/
int Pawn::getPawn_number()
{
	return this->pawn_number;
}

/*ZWRACA KOLOR PIONKA*/
Color Pawn::getPawn_color()
{
	return this->pawn_color;
}

/*WYŒWIETLA INFORMACJE O PIONKU*/
void Pawn::print_pawn()
{
	std::cout << "Pionek o numerze " << this->getPawn_number() << " posiada kolor: " << (this->getPawn_color()==Color::Red?"Red":"Green" )<< std::endl;
}

/*USTAWIA ¯YCIE PIONKA*/
void Pawn::set_live(bool a)
{
	this->live = a;
}

/*ZWRACA CZY PIONEK ZYJE*/
bool Pawn::get_live()
{
	return this->live;
}

/*USTAWIA KOLOR PIONKA*/
void Pawn::setPawn_color()
{
	this->pawn_shape.setFillColor(this->pawn_color);
}
