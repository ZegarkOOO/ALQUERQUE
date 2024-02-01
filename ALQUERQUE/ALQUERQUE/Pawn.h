#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Filds.h"

using namespace sf;

class Pawn
{
private:
	CircleShape pawn_shape; //shape okrêgu
	float pawn_radius = 20.f; //promieñ pionka
	Color pawn_color = Color::White; //domyœlny kolor pionka
	Vector2f pawn_position = Vector2f(0.f, 0.f); //domyœlna pozycja pionka
	int pawn_number{}; //numer pionka
	Vector2i pawn_position_array; //indeksy w tablicy zajêtoœci
	bool live = true; //czy ¿ywy?

public:
	Pawn();
	Pawn(int number, Color color);
	Pawn(int number, Color color, float x, float y, float radius = 20.f);
	~Pawn();

	Pawn& operator =(Pawn pion);

	void render(RenderTarget* target);

	bool update(const Vector2f mousePos, std::vector < Vector2i >& available_position, int& selected);
	bool update_move(const Vector2f mousePos, Vector2i &move);
	
	void setPawnPositionArray(int x, int y);
	Vector2i getPawnPositionArray();

	void setPawnPosition(float pos_x, float pos_y);
	void setPawnPosition(Vector2f vector_pos);

	void set_live(bool a);
	bool get_live();
	
	int getPawn_number();
	Color getPawn_color();
	void setPawn_color();
	void print_pawn();
};

