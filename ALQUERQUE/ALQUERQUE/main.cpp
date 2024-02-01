#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"

#define EXIT_SUCCES 0
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

using namespace std;
using namespace sf;

int main() {
	Event event{};
	Menu menu(event);
	return EXIT_SUCCES;
}