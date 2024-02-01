#pragma once
#include <iostream>

class Filds
{
public:
	//TABLICA Z POZYCJAMI NA OSI X
	const float arr_position_x[5][5] = {
		{450.f,600.f,750.f,900.f,1050.f},
		{450.f,600.f,750.f,900.f,1050.f},
		{450.f,600.f,750.f,900.f,1050.f},
		{450.f,600.f,750.f,900.f,1050.f},
		{450.f,600.f,750.f,900.f,1050.f}
	};

	//TABLICA Z POZYCJAMI NA OSI Y
	const float arr_position_y[5][5] = {
		{125.f,125.f,125.f,125.f,125.f},
		{275.f,275.f,275.f,275.f,275.f},
		{425.f,425.f,425.f,425.f,425.f},
		{575.f,575.f,575.f,575.f,575.f},
		{725.f,725.f,725.f,725.f,725.f}
	};

	//TABLICA ZAJÊTOŒCI
	int position_occupied[5][5]{-1};

	bool is_not_occupied(int x, int y);
	void print_position_occupied();
};

