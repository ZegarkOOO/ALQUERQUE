#include "DisplayRanking.h"

/*KONSTRUKTOR*/
DisplayRanking::DisplayRanking(RankingList& list)
{
	//STWORZENIE OKIENKA
	Event event{};
	window.create(VideoMode(windowWith, windowHeight), "Ranking", Style::Close);
	window.setFramerateLimit(60);
	this->setText(32, list);

	//PÊTLA G£ÓWNA
	while (window.isOpen()) {

		while (this->window.pollEvent(event)) {
			//ESC WYJŒCIE 
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {
				this->window.close();
			}
		}
		//NADANIE KOLORU T£A
		window.clear(Color(51, 50, 65, 255));

		//WYŒWIETLANIE LISTY RANKINGOWEJ
		window.draw(this->text);

		window.display();
	}
}

/*ZA£ADOWANIE CZCIONEK*/
void DisplayRanking::setFont()
{
	if (!this->font.loadFromFile("Tealand.ttf")) {
		std::cout << "font file is broken!\n";
	}
}

/*USTAWIANIE TEKSTU I ATRYBUTÓW*/
void DisplayRanking::setText(int size, RankingList& list)
{
	//PRZYPISANIE DO ZMIENNEJ STRINGSTREAM LISTY RANKINGOWEJ
	ss << list;

	this->text.setString(ss.str());
	this->setFont();
	this->text.setFont(this->font);
	this->text.setFillColor(Color::White);
	this->text.setCharacterSize(size);
	this->text.setPosition(
		this->window.getSize().x / 2.f - (this->text.getGlobalBounds().width / 2.f),
		50.f
	);
}