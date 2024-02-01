#pragma once
#include <iostream>
#include <SFML/Window.hpp>
#include <fstream>
#include "Button.h"
#include "Game.h"
#include "Confirm.h"
#include "mode.h"
#include "RankingList.h"
#include "DisplayRanking.h"

using namespace sf;

class Menu
{
private:
	RenderWindow windowMenu;
	const int menuWith{ 1000 };
	const int menuHeight{ 800 };
	bool isGameRunning = false;
	Texture texture;
	Sprite sprite;
	RankingList rank;

public:
	Menu(Event& event);
	Menu() = delete;
	~Menu() = default;
	
	void loadTexture();
};

