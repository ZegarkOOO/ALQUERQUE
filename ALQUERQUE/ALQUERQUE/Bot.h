#pragma once
#include <iostream>
#include <SFML/System.hpp>
#include <vector>
//#include "Pawn.h"

using namespace sf;

class Bot
{
private:
	int selected = -1; //wybrany pionek przez bota
	int tm_selected = -1;
	Vector2i move = {}; //wybrany ruch dla wybranego pionka
	Vector2i tm_move = {};
	int maxEval = -1; //wartoœc wybranego ruchu

public:
	void analyze_board_modified(int board[5][5]);
	int value_of_move(int tm_board[5][5], int p_pos_x, int p_pos_y, int mov_x, int mov_y);
	void set_max(int sel, Vector2i mov, int rank);
	Vector2i get_move();
	int get_selected();
	void reset();

};

