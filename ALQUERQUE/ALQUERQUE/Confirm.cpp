#include "Confirm.h"

/*KONSTRUKTIR G£ÓWNY*/
Confirm::Confirm(std::string text, int size)
{
	//STWORZENIE OKIENKA
	this->windowConfirm.create(VideoMode(this->confirmWith, this->confirmHeight), "Confirm", Style::None);
	this->windowConfirm.setFramerateLimit(60);

	//USTAWNIENIE TEKSTU
	this->setText(text, size);

	//TWORZENIE PRZYCISKÓW
	Button buttonY(50.f, 100.f, 100.f, 50.f, size, "YES", Color(38, 41, 31, 255),
		Color(200, 0, 0, 255), Color(100, 0, 0, 255));
	Button buttonN(250.f, 100.f, 100.f, 50.f, size, "NO", Color(38, 41, 31, 255), 
		Color(0, 165, 0, 255), Color(0, 64, 0, 255));

	//PETLA G£ÓWNA
	while (this->windowConfirm.isOpen()) {
		//AKTUALIZACJA PRZYCCISKÓW
		buttonN.update((Vector2f)Mouse::getPosition(this->windowConfirm));
		buttonY.update((Vector2f)Mouse::getPosition(this->windowConfirm));

		//SPRAWDZANIE WYBORU
		if (buttonY.isPressed()) {
			this->windowConfirm.close();
			sleep(milliseconds(150));
			this->isConfirmBool = true;
			//POTWIERDZENIE
		}
		if (buttonN.isPressed()) {
			this->windowConfirm.close();
			sleep(milliseconds(150));
			this->isConfirmBool = false;
			//ZAPRZECZENIE
		}

		this->windowConfirm.clear(Color(51, 50, 65, 255));

		//RENDEROWANIE PRZYCISKÓW I TEKSTU
		buttonN.render(&this->windowConfirm);
		buttonY.render(&this->windowConfirm);
		this->windowConfirm.draw(this->text);
		
		this->windowConfirm.display();
	}
}

/*DESTRUKTOR*/
Confirm::~Confirm()
{
}

/*ZWRACA CZY POTWIERDZONO*/
const bool Confirm::isConfirm() const
{
	return this->isConfirmBool;
}

/*USTAWIENIE TEKSTU*/
void Confirm::setText(std::string text, int size)
{
	this->text.setString(text);
	this->setFont();
	this->text.setFont(this->font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(size);
	this->text.setPosition(
		this->windowConfirm.getSize().x / 2.f - (this->text.getGlobalBounds().width / 2.f),
		50.f
	);
}

/*ZA£ADOWANIE CZCIONKI*/
void Confirm::setFont()
{
	if (!this->font.loadFromFile("Tealand.ttf")) {
		std::cout << "font file is broken!\n";
	}
}

