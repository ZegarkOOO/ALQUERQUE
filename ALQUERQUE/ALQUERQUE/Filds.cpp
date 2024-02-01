#include "Filds.h"

/*ZWRACA CZY POZYCJA JEST ZAJÊTA*/
bool Filds::is_not_occupied(int x, int y)
{
	return this->position_occupied[x][y] == -1;
	//true - wolny , false - zajety
}

/*WYŒWIETLA TABLICE ZAJÊTOŒCI*/
void Filds::print_position_occupied()
{
	std::cout << "Tablica zajetosci" << std::endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			std::cout << this->position_occupied[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
