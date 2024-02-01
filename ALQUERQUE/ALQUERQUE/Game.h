#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "Confirm.h"
#include "Menu.h"
#include "Pawn.h"
#include "Filds.h"
#include "Record.h"
#include "RankingList.h"
#include "Bot.h"
#include "TheEnd.h"

using namespace sf;

class Game
{
private:
	RenderWindow windowGame; //okienko
	const int gameWith{ 1500 }; //szeroko�� okienka
	const int gameHeight{ 850 }; //wysoko�� okienka
	Pawn pawns[24]; //tablica pionk�w
	Filds filds; //obiekt z tablicami 
	Texture texture; //tekstura
	Sprite sprite; //sprite
	Font font; //czcionka
	Text player1, player2, timerText, moveText; //teksty
	int counttime = 0; //licznik czasu
	int countMove = 0; //licznik ruch�w

	int pl1 = 0; //wygrana?
	int pl2 = 0;

	int selected = -1; //wybrany pionke
	std::vector < Vector2i > available_position; //wektor z dostepnymi pozycjami
	bool display_available_position = true; //dost�p do aktualizowania pionk�w
	Pawn* ptr_new_pawns; //wska�nik na nowe mo�liwe ruchy
	Vector2i move; //zmienna przechowuj�ca koordynaty wybranego pionka z tablicy zaj�to�ci
	bool move_player = true; // ruch gracza true-zielony false-czerwony


public:
	Game(Event& event, bool choice, String a, String b); //konstruktor 
	Game() = delete; 
	~Game();

	//Function
	void create24pawns();
	void setPawnPosition();
	void render_pawns();
	void update_pawns();
	void render_ptr_pawns();
	void update_ptr_pawns();
	void possible_transitions();
	void bot_move(String a, String b);

	void loadTexture();
	void setFont();
	void setText(String player_a, String player_b);

	int vector_module(Vector2i a, Vector2i b);
	Vector2i vector_deleted_move_pawn(Vector2i a, Vector2i b);

	int get_counttime();
	int get_countmove();

	//funkcja sprawdzaj�ca wygranie i wy�wietlaj�ca wynik
	bool check_win(String a, String b);
};

