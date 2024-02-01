#include "mode.h"

mode::mode(std::string text, int size)
{
	//TWORZENIE OKIENKA
	Event event{};
	this->choice_mode = true;
	windowMode.create(VideoMode(modeWith, modeHeight), "Mode", Style::None);
	windowMode.setFramerateLimit(60);

	//TWORZENIE PRZYCISKÓW
	Button multi((modeWith / 3) - 50.f, 100.f, 100.f, 50.f, size, "Multi", Color(38, 41, 31, 255),
		Color(0, 165, 0, 255), Color(0, 64, 0, 255));
	Button single((modeWith / 3) * 2 - 50.f, 100.f, 100.f, 50.f, size, "Single", Color(38, 41, 31, 255),
		Color(0, 165, 0, 255), Color(0, 64, 0, 255));

	Button start((modeWith / 2) - 100.f, 100.f, 200.f, 50.f, size, "START", Color(38, 41, 31, 255),
		Color(0, 165, 0, 255), Color(0, 64, 0, 255));

	//BIA£E POLA POD INPUT-BOXY
	this->shape1.setFillColor(Color::White);
	this->shape2.setFillColor(Color::White);
	this->shape1.setPosition(this->windowMode.getSize().x / 3.f, 250.f);
	this->shape2.setPosition(this->windowMode.getSize().x / 3.f, 550.f);
	this->shape1.setSize(Vector2f(500.f, 60.f));
	this->shape2.setSize(Vector2f(500.f, 60.f));

	//USTAWIANIE INPUTBOXÓW
	setText(text, size);
	setInputFilds();

	//PÊTLA G£ÓWNA
	while (windowMode.isOpen()) {
		while (windowMode.pollEvent(event)) {
			//AKTUALIZACJA PRZYCISKÓW
			multi.update((Vector2f)Mouse::getPosition(this->windowMode));
			single.update((Vector2f)Mouse::getPosition(this->windowMode));

			if (!player1.empty() && !player2.empty()) {
				start.update((Vector2f)Mouse::getPosition(this->windowMode));
			}

			//SPRAWDZANIE WCIŒNIÊCIA PRZYSISKÓW
			if (multi.isPressed()) {
				sleep(milliseconds(150));
				this->choice_mode = false;
			}
			if (single.isPressed()) {
				sleep(milliseconds(150));
				this->choice_mode = true;
			}
			if (start.isPressed()) {
				for (int i = 0; i < player1.length(); i++) {
					if (player1[i] == ' ')player1[i] = '_';
				}
				for (int i = 0; i < player2.length(); i++) {
					if (player2[i] == ' ')player2[i] = '_';
				}
				this->windowMode.close();
			}

			//WYBÓR INPUTBOXA DO WPISYWANIA
			if (shape1.getGlobalBounds().contains((Vector2f)Mouse::getPosition(this->windowMode))) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					input_box_access = true;
				}
			}
			if (shape2.getGlobalBounds().contains((Vector2f)Mouse::getPosition(this->windowMode))) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					input_box_access = false;
				}
			}
			
			//WPISYWANIE I USUWANIE Z KLAWIATURY DO INPUTBOXA W ZALE¯NOŒCI OD WYBRANEGO
			if (input_box_access) {
				//WPISYWANIE DO 1
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode >= 32 && event.text.unicode <= 127)
					{
						if(player1.size() < 30)
							player1 += event.text.unicode;
						player1Text.setString(player1);
					}
				}
				//USUWANIE Z 1
				if (event.type == Event::KeyPressed && event.key.code == Keyboard::BackSpace) {
					if (!player1.empty()) {
						player1.pop_back();
						player1Text.setString(player1);
					}
				}
			}
			if (!input_box_access && choice_mode == false) {
				//WPISYWANIE DO 2
				if (event.type == sf::Event::TextEntered) {
					if (event.text.unicode >= 32 && event.text.unicode <= 127)
					{
						if(player2.size() < 30)
							player2 += event.text.unicode;
						player2Text.setString(player2);
					}
				}
				//USUWANIE Z 2
				if (event.key.code == sf::Keyboard::BackSpace) {
					if (!player2.empty()) {
						player2.pop_back();
						player2Text.setString(player2);
					}
				}
			}
			
		}

		windowMode.clear(Color(51, 50, 65, 255));

		//RENDER PRZYCISKÓW I TEKSTU
		multi.render(&windowMode);
		single.render(&windowMode);
		start.render(&windowMode);
		this->windowMode.draw(this->text);

		//RYSOWANIE PIERWSZEGO GRACZA
		windowMode.draw(shape1);
		windowMode.draw(player1Text);
		windowMode.draw(name_input_box1);

		//DORYSOWANIE DRUGIEGO GRACZA W TRYBIE MULTI
		if (choice_mode == false) {
			windowMode.draw(shape2);
			windowMode.draw(player2Text);
			windowMode.draw(name_input_box2);
		}

		windowMode.display();
	}

}

/*DESTRUKTOR*/
mode::~mode()
{
}

/*ZWRACA WYBÓR MULTI/SINGLE*/
bool mode::bool_mode()
{
	return this->choice_mode;
}

/*USTAWIENIE TEKSTU NAG£ÓWKOWEGO*/
void mode::setText(std::string text, int size)
{
	this->text.setString(text);
	this->setFont();
	this->text.setFont(this->font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(size);
	this->text.setPosition(
		this->windowMode.getSize().x / 2.f - (this->text.getGlobalBounds().width / 2.f),
		50.f
	);
}

/*ZA£ADOWANIE CZCIONKI*/
void mode::setFont()
{
	if (!this->font.loadFromFile("Tealand.ttf")) {
		std::cout << "font file is broken!\n";
	}
}

/*USTAWEIENIE TEKSTÓW I INPUTBOXÓW*/
void mode::setInputFilds()
{
	//USTAWIENIE INPUT-BOXA 1
	this->player1Text.setString(this->player1);
	this->player1Text.setFont(this->font);
	this->player1Text.setFillColor(Color::Black);
	this->player1Text.setCharacterSize(27);
	this->player1Text.setPosition(shape1.getPosition().x + 10.f, shape1.getPosition().y + 10);

	//USTAWIENIE INPUT-BOXA 2
	this->player2Text.setString(this->player2);
	this->player2Text.setFont(this->font);
	this->player2Text.setFillColor(Color::Black);
	this->player2Text.setCharacterSize(27);
	this->player2Text.setPosition(shape2.getPosition().x + 10.f, shape2.getPosition().y + 10);

	//USTAWIENIE GRACZA 1 TEXT
	this->name_input_box1.setString("Name player 1:     ");
	this->name_input_box1.setFont(this->font);
	this->name_input_box1.setFillColor(Color::White);
	this->name_input_box1.setCharacterSize(27);
	this->name_input_box1.setPosition(shape1.getPosition().x - name_input_box1.getGlobalBounds().width, shape1.getPosition().y + 10);
		  
	//USTAWIENIE GRACZA 2 TEXT
	this->name_input_box2.setString("Name player 2:     ");
	this->name_input_box2.setFont(this->font);
	this->name_input_box2.setFillColor(Color::White);
	this->name_input_box2.setCharacterSize(27);
	this->name_input_box2.setPosition(shape2.getPosition().x - name_input_box2.getGlobalBounds().width, shape2.getPosition().y + 10);
}


/*ZWRACA NAZWÊ 1 GRACZA*/
String mode::get_name()
{
	return this->player1;
}

/*ZWRACA NAZWÊ 2 GRACZA*/
String mode::get_name2()
{
	return this->player2;
}
