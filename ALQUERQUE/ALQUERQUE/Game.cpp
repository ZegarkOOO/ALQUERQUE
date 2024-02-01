#include "Game.h"

Game::Game(Event& event, bool choice, String a, String b)
{

	//CREATE WINDOW
	this->windowGame.create(VideoMode(this->gameWith, this->gameHeight), "ALQUERQUE game", Style::Close);
	this->windowGame.setFramerateLimit(60);

	//SET FONT, TEXTURE, TEXT
	this->setFont();
	this->loadTexture();
	this->texture.setSmooth(true);
	this->setText(a, b);
	
	//CREATE AND POSITIONING PAWNS
	this->create24pawns();
	this->setPawnPosition();

	//START CLOCK
	Clock clock;

	//MAIN LOOP
	while (windowGame.isOpen()) {

		//TIMER
		int timer = clock.getElapsedTime().asSeconds();
		if (timer > 0) {
			counttime++;
			timerText.setString("CZAS: " + ((counttime / 60 < 10 ? "0" : "") + std::to_string(int(counttime / 60)) + ":" 
				+ (counttime%60 < 10 ? "0" : "") + std::to_string(counttime % 60)));
			clock.restart();
		}

		//AKTUALIZACJA LICZNIKA RUCHÓW
		moveText.setString("RUCH: " + std::to_string(countMove));


		while (windowGame.pollEvent(event)) {

			//EXIT BUTTON TO MENU
			if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)) {

				//POTWIERDZENIE WYJSCIA
				Confirm confirm_exit_game("Do you want to exit?", 27);
				if (confirm_exit_game.isConfirm()) {
					windowGame.close();

					//POWRÓT DO MENU
					Menu menu(event);
				}
			}

			//AKTUALIZACJA PIONKÓW
			update_pawns();
			
			//AKTUALIZACJA MOO¯LIWYCH RUCHÓW
			update_ptr_pawns();

			//ANULOWANIE WYBORU PIONKA
			if (Mouse::isButtonPressed(Mouse::Right) && display_available_position == false) {

				//powrót do poprzedniego koloru przed wybraniem
				pawns[selected].setPawn_color(); 

				//brak wybranego pionka
				selected = -1; 

				//mo¿liwoœæ aktualizowania pionków pod wzglêdem ruchu
				display_available_position = true; 

				//usuwanie i czyszczenie wczeœniejszych mozliwych ruchów
				available_position.clear();
				delete[]ptr_new_pawns;
			}

			//TWORZENIE DYNAMICZNIE MO¯LIWYCH RUCHÓW
			possible_transitions();

			//WYBÓR BOTA
			if (choice && !move_player) {
				Bot bot;
				sleep(milliseconds(150));
				bot.analyze_board_modified(filds.position_occupied);

				selected = bot.get_selected(); //przypisanie wybranego
				move = bot.get_move(); //przypisanie ruchu
				bot_move(a, b);
				bot.reset();
			}

			//SPRAWDZANIE WYGRANEJ i zapisanie do rankingu
			check_win(a, b);

		}
		//WYSWIETLANIE KOLORU T£A I TEXTURY
		this->windowGame.clear(Color::Color(220, 250, 205));
		this->windowGame.draw(this->sprite);

		this->windowGame.draw(player1); // NICK PIERWSZEGO GRACZA
		this->windowGame.draw(player2); // NICK DRUGIEGO GRACZA
		this->windowGame.draw(timerText); // WYŒWIETLANIE TIMERA
		this->windowGame.draw(moveText); // WYŒWIETLANIE LICZBY RUCHÓW

		// RENDEROWANIE PIONKÓW I MO¯LIWYCH RUCHÓW
		this->render_pawns();
		this->render_ptr_pawns();
		
		windowGame.display();
	}
}

/*DESTRUKTOR*/
Game::~Game()
{
}

/*FUNKCJA TWORZ¥CA PIONKI*/	
void Game::create24pawns()
{
	for (int i = 0; i < 24; i++) {
		Pawn pawn(i, i < 12 ? Color::Green : Color::Red);
		this->pawns[i] = pawn;
	}
}

/*FUNKCJA USTAWIAJ¥CA PIONKI NA POZYCJACH*/
void Game::setPawnPosition()
{
	int m = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i != 2 || j != 2) {			
				//PRZYPISANIE KOORDYNATÓW Z TABLIC POZYCJI DO KA¯DEGO PIONKA
				this->pawns[m].setPawnPosition(filds.arr_position_x[j][i], filds.arr_position_y[j][i]);

				//ZAPIS NUMERU PIONKA DO TABLICY ZAJÊTOŒCI
				filds.position_occupied[j][i] = this->pawns[m].getPawn_number();

				//ZAPIS KOORDYNATÓW Z TABLICY ZAJÊTOŒCI DO KO¯DEGO PIONKA
				this->pawns[m].setPawnPositionArray(j, i); 
				m=m+1;			
			}
			else if (i == 2 && j == 2) {
				//NA SRODKU PUSTE POLE
				filds.position_occupied[i][j] = -1;
			}
		}
	}
}

/*RENDEROWNAIE PIONKÓW*/
void Game::render_pawns()
{
	for (int i = 0; i < 24; i++) {
		this->pawns[i].render(&this->windowGame);
	}
}

/*AKTUALIZACJA PIONKOW POD KONTEM RUCHU*/
void Game::update_pawns()
{
	if (display_available_position) {
		if (move_player) {
			
			//AKTUALIZOWANIE PIONKÓW GRACZA 1
			for (int i = 0; i < 12; i++) {
				this->pawns[i].update((Vector2f)Mouse::getPosition(this->windowGame), available_position, this->selected);
			}
		}
		else {

			//AKTUALIZOWANIE PIONKÓW GRACZA 2
			for (int i = 12; i < 24; i++) {
				this->pawns[i].update((Vector2f)Mouse::getPosition(this->windowGame), available_position, this->selected);
			}
		}
	}
}

/*RENDEROWANIE MOZLIWYCH RUCHÓW*/
void Game::render_ptr_pawns()
{
	for (int i = 0; i < available_position.size(); i++) {
		ptr_new_pawns[i].render(&windowGame);
	}
}

/*FUNKCJA WYKONYWANA PODCZAS RUCHU PIONKA NA NOW¥ POZYCJE*/	
void Game::update_ptr_pawns()
{
	for (int i = 0; i < available_position.size(); i++) {
		if (ptr_new_pawns[i].update_move((Vector2f)Mouse::getPosition(this->windowGame), move) == true) {
			Vector2i temp_array_index = pawns[selected].getPawnPositionArray();

			//PRZESKOCZENIE PIONKA PRZECIWNIKA
			if (vector_module(temp_array_index, move) == 2) {
				pawns[filds.position_occupied[(temp_array_index.x + move.x) / 2][(temp_array_index.y + move.y) / 2]].set_live(false); // usun/przestan wyswietlac
				filds.position_occupied[(temp_array_index.x + move.x) / 2][(temp_array_index.y + move.y) / 2] = -1; // USUÑ Z TABLICY ZAJÊTOŒCI 
			}
			//PRZESUNIÊCIE PIONKA NA WYBRAN¥ POZYCJE
			pawns[selected].setPawnPosition(
				filds.arr_position_x[available_position[i].x][available_position[i].y],
				filds.arr_position_y[available_position[i].x][available_position[i].y]);

			//ZMIANA W TABLICY ZAJÊTOŒCI
			filds.position_occupied[temp_array_index.x][temp_array_index.y] = -1;
			pawns[selected].setPawnPositionArray(move.x, move.y);
			filds.position_occupied[move.x][move.y] = pawns[selected].getPawn_number();
			
			//INKREMENTACJA LICZNIKA RUCHÓW
			countMove++;

			//USTAWIENIE BRAK WYBRANEGO PIONKA 
			pawns[selected].setPawn_color(); //powrót do default color
			selected = -1;
			display_available_position = true;

			//USUWANIE WCZESNIEJSZYCH MO¯LIWOŒCI RUCHÓW
			available_position.clear();
			delete[]ptr_new_pawns;

			//RUCH PRZECIWNIKA
			move_player = !move_player;

			/////////////////////////
			//filds.print_position_occupied();
		}
	}
}

/*AKTUALIZOWANIE MOZLIWWYCH RUCHÓW*/
void Game::possible_transitions()
{
	if (this->selected != -1 && this->display_available_position == true) {

		Vector2i temp = pawns[selected].getPawnPositionArray();

		//SPRAWDZANIE WOLNYCH RUCHÓW I PRZYPISYWANIE DO WEKTORA:
		//w lewo
		if (temp.x > 0) {
			if (filds.is_not_occupied(temp.x - 1, temp.y)) {
				available_position.push_back(Vector2i(temp.x - 1, temp.y));
			}
			else if (filds.is_not_occupied(temp.x - 1, temp.y)==false && pawns[filds.position_occupied[temp.x - 1][temp.y]].getPawn_color() != pawns[selected].getPawn_color()) 
			{
				if (temp.x > 1) {
					if (filds.is_not_occupied(temp.x - 2, temp.y)) {
						available_position.push_back(Vector2i(temp.x - 2, temp.y));
					}
				}
			}
		}
		//w prawo
		if (temp.x < 4) {
			if (filds.is_not_occupied(temp.x + 1, temp.y)) {
				available_position.push_back(Vector2i(temp.x + 1, temp.y));
			}
			else if (filds.is_not_occupied(temp.x + 1, temp.y) == false && pawns[filds.position_occupied[temp.x + 1][temp.y]].getPawn_color() != pawns[selected].getPawn_color()) {
				if (temp.x < 3) {
					if (filds.is_not_occupied(temp.x + 2, temp.y)) {
						available_position.push_back(Vector2i(temp.x + 2, temp.y));
					}
				}
			}
		}
		// do góry
		if (temp.y > 0) {
			if (filds.is_not_occupied(temp.x, temp.y - 1)) {
				available_position.push_back(Vector2i(temp.x, temp.y - 1));
			}
			else if (filds.is_not_occupied(temp.x, temp.y - 1) == false && pawns[filds.position_occupied[temp.x][temp.y - 1]].getPawn_color() != pawns[selected].getPawn_color()) {
				if (temp.y > 1) {
					if (filds.is_not_occupied(temp.x, temp.y - 2)) {
						available_position.push_back(Vector2i(temp.x, temp.y - 2));
					}
				}
			}
		}
		//na dó³
		if (temp.y < 4) {
			if (filds.is_not_occupied(temp.x, temp.y + 1)) {
				available_position.push_back(Vector2i(temp.x, temp.y + 1));
			}
			else if (filds.is_not_occupied(temp.x, temp.y + 1) == false && pawns[filds.position_occupied[temp.x][temp.y + 1]].getPawn_color() != pawns[selected].getPawn_color()) {
				if (temp.y < 3) {
					if (filds.is_not_occupied(temp.x, temp.y + 2)) {
						available_position.push_back(Vector2i(temp.x, temp.y + 2));
					}
				}
			}
		}
		//po skosach
		if ((temp.x + temp.y) % 2 == 0) {

			//lewa gora
			if(temp.x > 0 && temp.y > 0){
				if (filds.is_not_occupied(temp.x - 1, temp.y - 1)) {
					available_position.push_back(Vector2i(temp.x - 1, temp.y - 1));
				}
				else if (filds.is_not_occupied(temp.x - 1, temp.y - 1) == false && pawns[filds.position_occupied[temp.x - 1][temp.y - 1]].getPawn_color() != pawns[selected].getPawn_color()) {
					if (temp.x > 1 && temp.y > 1) {
						if(filds.is_not_occupied(temp.x - 2, temp.y - 2))
						available_position.push_back(Vector2i(temp.x - 2, temp.y - 2));
					}
				}
			}
			//prawa dó³
			if(temp.x < 4 && temp.y < 4){
				if (filds.is_not_occupied(temp.x + 1, temp.y + 1)) {
					available_position.push_back(Vector2i(temp.x + 1, temp.y + 1));
				}
				else if (filds.is_not_occupied(temp.x + 1, temp.y + 1) == false && pawns[filds.position_occupied[temp.x + 1][temp.y + 1]].getPawn_color() != pawns[selected].getPawn_color()) {
					if (temp.x < 3 && temp.y < 3) {
						if (filds.is_not_occupied(temp.x + 2, temp.y + 2))
							available_position.push_back(Vector2i(temp.x + 2, temp.y + 2));
					}
				}
			}
			//prawa góra
			if(temp.x < 4 && temp.y > 0){
				if (filds.is_not_occupied(temp.x + 1, temp.y - 1)) {
					available_position.push_back(Vector2i(temp.x + 1, temp.y - 1));
				}
				else if (filds.is_not_occupied(temp.x + 1, temp.y - 1) == false && pawns[filds.position_occupied[temp.x + 1][temp.y - 1]].getPawn_color() != pawns[selected].getPawn_color()) {
					if (temp.x < 3 && temp.y > 1) {
						if (filds.is_not_occupied(temp.x + 2, temp.y - 2))
							available_position.push_back(Vector2i(temp.x + 2, temp.y - 2));
					}
				}

			}
			//lewy dó³
			if(temp.x > 0 && temp.y < 4){
				if (filds.is_not_occupied(temp.x - 1, temp.y + 1)) {
					available_position.push_back(Vector2i(temp.x - 1, temp.y + 1));
				}
				else if (filds.is_not_occupied(temp.x - 1, temp.y + 1) == false && pawns[filds.position_occupied[temp.x - 1][temp.y + 1]].getPawn_color() != pawns[selected].getPawn_color()) {
					if (temp.x > 1 && temp.y < 3) {
						if (filds.is_not_occupied(temp.x - 2, temp.y + 2))
							available_position.push_back(Vector2i(temp.x - 2, temp.y + 2));
					}
				}
			}
		}
		unsigned int temp_size_vec = available_position.size();
		//std::cout <<"Rozmiar vektora available: " << temp_size_vec << std::endl;
		
		//TWORZENIE DYNAMICZNIE MO¯LIWYCH PRZEJŒÆ
		if (available_position.size() > 0) {
			ptr_new_pawns = new Pawn[temp_size_vec + 1];
			for (int i = 0; i < temp_size_vec; i++) {
				Pawn temp2(100 + i, Color::Yellow, 
					filds.arr_position_x[available_position[i].x][available_position[i].y], 
					filds.arr_position_y[available_position[i].x][available_position[i].y], 40.f);
				temp2.setPawnPositionArray(available_position[i].x, available_position[i].y);
				ptr_new_pawns[i] = temp2;
			}
			display_available_position = false;
		}
		else {
			//POWRÓT DO STANU POCZ¥TKOWEGO GDY BRAK MOZLIWOŒCI RUCHU
			pawns[selected].setPawn_color(); //powrót do default color
			this->display_available_position = true;
			selected = -1;
		}
	}
}

/*RUCH BOTA*/
void Game::bot_move(String a, String b)
{
	if (check_win(a,b) == false) {
		Vector2i temp_array_index = pawns[selected].getPawnPositionArray();

		//PRZESKOCZENIE PIONKA PRZECIWNIKA
		if (vector_module(temp_array_index, move) == 2) {
			pawns[filds.position_occupied[(temp_array_index.x + move.x) / 2][(temp_array_index.y + move.y) / 2]].set_live(false); // usun/przestan wyswietlac
			filds.position_occupied[(temp_array_index.x + move.x) / 2][(temp_array_index.y + move.y) / 2] = -1; // USUÑ Z TABLICY ZAJÊTOŒCI 
		}
		//PRZESUNIÊCIE PIONKA NA WYBRAN¥ POZYCJE
		pawns[selected].setPawnPosition(
			filds.arr_position_x[move.x][move.y],
			filds.arr_position_y[move.x][move.y]);

		//ZMIANA W TABLICY ZAJÊTOŒCI
		filds.position_occupied[temp_array_index.x][temp_array_index.y] = -1;
		pawns[selected].setPawnPositionArray(move.x, move.y);
		filds.position_occupied[move.x][move.y] = pawns[selected].getPawn_number();

		//INKREMENTACJA LICZNIKA RUCHÓW
		countMove++;

		//USTAWIENIE BRAK WYBRANEGO PIONKA 
		pawns[selected].setPawn_color(); //powrót do default color
		selected = -1;
		display_available_position = true;


		//RUCH PRZECIWNIKA
		move_player = !move_player;

		/////////////////////////
		filds.print_position_occupied(); 
	}
}

/*ZA£ADOWANIE TEKSTURY NA T£O*/
void Game::loadTexture()
{
	if (!texture.loadFromFile("GAMEsheets.png"))
	{
		std::cerr << "failed to load image" << std::endl;
		exit(1);
	}
	this->sprite.setTexture(this->texture);
}

/*ZA£ADOWANIE CZCIONEK Z PLIKU*/
void Game::setFont()
{
	if (!this->font.loadFromFile("Tealand.ttf")) {
		std::cout << "font file is broken!\n";
	}
}

/*USTAWIENIE WSZYSTKICH POTRZEBNYCH ATRYBUTÓW WYŒWIETLANYCH TEKSTÓW*/
void Game::setText(String player_a, String player_b)
{
	//ROZMIAR NAPPISÓW
	player1.setCharacterSize(30);
	player2.setCharacterSize(30);
	timerText.setCharacterSize(30);
	moveText.setCharacterSize(30);

	//TEXT NAPISÓW
	player1.setString("Gracz 1: " + player_a);
	player2.setString("Gracz 2: " + player_b);
	moveText.setString("RUCH: " + std::to_string(countMove));
	timerText.setString("CZAS: " + ((counttime / 60 < 10 ? "0" : "") + std::to_string(int(counttime / 60)) + ":" 
		+ (counttime%60<10 ? "0" : "") + std::to_string(counttime % 60)));

	//KOLOR NAPISÓW
	player1.setFillColor(Color::Black);
	player2.setFillColor(Color::Black);
	timerText.setFillColor(Color::Black);
	moveText.setFillColor(Color::Black);

	//CZCIONKA NAPISÓW
	player1.setFont(font);
	player2.setFont(font);
	timerText.setFont(font);
	moveText.setFont(font);

	//POZYCJA NAPISÓW
	player1.setPosition(gameWith / 5.f - player1.getGlobalBounds().width/2, 20.f);
	player2.setPosition(gameWith / 5.f * 4 - player2.getGlobalBounds().width / 2, 20.f);
	timerText.setPosition(gameWith / 10.f - timerText.getGlobalBounds().width / 2, 100.f);
	moveText.setPosition(gameWith / 10.f - timerText.getGlobalBounds().width / 2, 150.f);
	
}

/*OBLICZANIE MODU£U (ODLEG£OŒCI) Z WEKTORÓW*/
int Game::vector_module(Vector2i a, Vector2i b)
{
	return sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
}

/*FUNKCJA OBLICZAJ¥CA WEKTOR RÓWNO POMIÊDZY DWOMA INNYMI - ZBITY PIONEK*/
Vector2i Game::vector_deleted_move_pawn(Vector2i a, Vector2i b)
{
	return Vector2i((a.x + b.x) / 2, (a.y + b.y) / 2);
}

/*FUNKCJA ZWRACA CZAS ROZGRYWKI*/
int Game::get_counttime()
{
	return counttime;
}

/*FUNKCJA ZWRACA CZAS ROZGRYWKI*/
int Game::get_countmove()
{
	return countMove;
}

bool Game::check_win(String a, String b)
{
	Event event{};

	for (int i = 0; i < 12; i++) {
		if (pawns[i].get_live() == false) {
			pl1++;
		}
	}

	for (int i = 12; i < 24; i++) {
		if (pawns[i].get_live() == false) {
			pl2++;
		}
	}

	if (pl2 == 12) {
		this->windowGame.close();

		//ZAPIS ROZGRYWKI DO RANKINGU
		RankingList rank;
		rank.add(Record(a, b, countMove, counttime));
		rank.saveFile();
		
		//okienko wygrania 
		TheEnd theend(a, countMove, counttime);
		return true;
	}

	if (pl1 == 12) {
		this->windowGame.close();

		//ZAPIS ROZGRYWKI DO RANKINGU
		RankingList rank;
		rank.add(Record(b, a, countMove, counttime));
		rank.saveFile();

		//okienko wygrania
		TheEnd theend(b, countMove, counttime);
		return true;
	}

	pl1 = 0;
	pl2 = 0;

	return false;
}
