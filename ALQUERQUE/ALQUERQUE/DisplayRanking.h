#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "RankingList.h"
#include "Record.h"


using namespace sf;

class DisplayRanking
{
private:
	const int windowWith{ 1000 };
	const int windowHeight{ 800 };

	RenderWindow window;
	Text text;
	Font font;
	ostringstream ss;

public:
	DisplayRanking(RankingList& list);
	void setFont();
	void setText(int size, RankingList& list);




};

