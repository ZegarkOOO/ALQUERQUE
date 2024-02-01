#include "Menu.h"

Menu::Menu(Event& event) {

	//TWORZNENIE OKNA I £ADOWNANIE TEKSTURY
	windowMenu.create(VideoMode(Menu::menuWith, Menu::menuHeight),  "ALQUERQUE menu", Style::Close);
	windowMenu.setFramerateLimit(60);

	//ZA£ADOWANIE TEKSTURY
	this->loadTexture();

	//AKTUALIZACJA RANKINGU DANYMI Z PLIKU
	this->rank.loadFile();

	//TWORZENIE PRZYCISKÓW
	Button button_Play(150.f, 387.f, 700.f, 123.f, 35, "PLAY", 
		Color::Color(237,173,155,255), Color::Color(25,80,35,255), Color::Color(225, 79, 38, 255));

	Button button_Ranking(150.f, 590.f, 315.f, 105.f, 35, "RANKING", 
		Color::Color(237, 173, 155, 255), Color::Color(25, 80, 35, 255), Color::Color(225, 79, 38, 255));

	Button button_Exit(535.f, 590.f, 315.f, 105.f, 35, "EXIT", 
		Color::Color(237, 173, 155, 255), Color::Color(25, 80, 35, 255), Color::Color(225, 79, 38, 255));

	while (this->windowMenu.isOpen()) {
		
		while (this->windowMenu.pollEvent(event)) {

			//EXIT BUTTONS
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape || button_Exit.isPressed())) {

				//okienko zapytania czy napewno chcesz wyjsc?
				Confirm confirm_exit("Do you want to exit?", 27);
				if (confirm_exit.isConfirm()) {
					this->windowMenu.close();
				}
			}

			if (!this->isGameRunning) {

				//AKTUALIZOWANIE PRZYCISKÓW
				button_Play.update((Vector2f)Mouse::getPosition(this->windowMenu));
				button_Ranking.update((Vector2f)Mouse::getPosition(this->windowMenu));
				button_Exit.update((Vector2f)Mouse::getPosition(this->windowMenu));

				//PRZYCISK PLAY
				if (button_Play.isPressed()) {
					this->isGameRunning = button_Play.isPressed();
					this->windowMenu.close();

					//WYBÓR TRYBU
					mode Mode("WYBIERZ TRYB", 27);
					if (Mode.bool_mode()) {
						//SINGLE PLAYER
						Game game(event, true, Mode.get_name(), "BOT");//single
					}
					else {
						//MULTIPLAYER
						Game game(event, false, Mode.get_name(), Mode.get_name2());//multi
					}
					this->isGameRunning = false;
				}

				//PRZYCISK RANKING
				if (button_Ranking.isPressed()) {
					DisplayRanking rankingDisp(rank);
					//rank.display();
				}
			}			
		}
		//T£O MENU I TEKSTURA
		this->windowMenu.clear(Color::Cyan);
		this->windowMenu.draw(this->sprite);

		//RENDEROWANIE PRZYCISKÓW
		button_Play.render(&this->windowMenu);
		button_Ranking.render(&this->windowMenu);
		button_Exit.render(&this->windowMenu);

		this->windowMenu.display();
	}
}

/*ZA£ADOWANIE TEKSTURY Z PLIKU*/
void Menu::loadTexture()
{
	if (!texture.loadFromFile("MENUsheets.png"))
	{
		std::cerr << "failed to load image" << std::endl;
		exit(1);
	}
	this->sprite.setTexture(this->texture);
}

