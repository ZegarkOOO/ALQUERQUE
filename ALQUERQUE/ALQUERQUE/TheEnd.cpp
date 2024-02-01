#include "TheEnd.h"

/*KONSTUKTOR Z PÊTL¥ G£ÓWN¥*/
TheEnd::TheEnd(String winner, int countmove, int counttime)
{
	//twoarzenie okienka
	Event event{};
	window.create(VideoMode(windowWith, windowHeight), "THE END", Style::Close);

	//usatwienie napisów
	napis.setString("The WINNER is");
	this->setFont();
	napis.setCharacterSize(45);
	napis.setFillColor(Color::White);
	napis.setFont(font);
	napis.setPosition(this->window.getSize().x / 2.f 
		- (this->napis.getGlobalBounds().width / 2.f),
		50.f);

	this->winner.setString(winner);
	this->winner.setCharacterSize(60);
	this->winner.setFillColor(Color::Green);
	this->winner.setFont(font);
	this->winner.setPosition(this->window.getSize().x / 2.f
		- (this->winner.getGlobalBounds().width / 2.f),
		200.f);

	this->cmove.setString(std::to_string(countmove));
	this->cmove.setCharacterSize(45);
	this->cmove.setFillColor(Color::White);
	this->cmove.setFont(font);
	this->cmove.setPosition(this->window.getSize().x / 4.f
		- (this->cmove.getGlobalBounds().width / 2.f),
		450.f);

	this->labelmove.setString("Number of moves");
	this->labelmove.setCharacterSize(30);
	this->labelmove.setFillColor(Color::White);
	this->labelmove.setFont(font);
	this->labelmove.setPosition(this->window.getSize().x / 4.f
		- (this->labelmove.getGlobalBounds().width / 2.f),
		400.f);

	this->ctime.setString(((counttime / 60 < 10 ? "0" : "")
		+ to_string(int(counttime / 60))
		+ ":"
		+ (counttime % 60 < 10 ? "0" : "")
		+ to_string(counttime % 60)));
	this->ctime.setCharacterSize(45);
	this->ctime.setFillColor(Color::White);
	this->ctime.setFont(font);
	this->ctime.setPosition(this->window.getSize().x / 4.f * 3.f
		- (this->ctime.getGlobalBounds().width / 2.f),
		450.f);

	this->labeltime.setString("Time");
	this->labeltime.setCharacterSize(30);
	this->labeltime.setFillColor(Color::White);
	this->labeltime.setFont(font);
	this->labeltime.setPosition(this->window.getSize().x / 4.f * 3.f
		- (this->labeltime.getGlobalBounds().width / 2.f),
		400.f);

	//przycisk powrotu do menu
	Button exit_to_menu((windowWith / 2) - 300.f, 600.f, 600.f, 100.f, 32, "MENU", Color(38, 41, 31, 255),
		Color(0, 165, 0, 255), Color(0, 64, 0, 255));
	
	//pêtla g³ówna
	while (window.isOpen()) {
		while (this->window.pollEvent(event)) {
			exit_to_menu.update((Vector2f)Mouse::getPosition(this->window));

			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
				this->window.close();
			}

			if (exit_to_menu.isPressed()) {
				this->window.close();
				Menu menu(event);
			}
			
		}
		
		//rysowanie i renderownie
		window.clear(Color(51, 50, 65, 255));
		window.draw(this->cmove);
		window.draw(this->ctime);
		window.draw(this->napis);
		window.draw(this->winner);
		window.draw(this->labelmove);
		window.draw(this->labeltime);

		exit_to_menu.render(&this->window);
		window.display();
	}

}

/*£ADOWANIE CZCIONKI*/
void TheEnd::setFont()
{
	if (!this->font.loadFromFile("Tealand.ttf")) {
		std::cout << "font file is broken!\n";
	}
}
