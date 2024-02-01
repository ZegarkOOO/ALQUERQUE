#include "RankingList.h"

/*KONSTRUKTOR*/
RankingList::RankingList()
{
}

/*DESTRUKTOR*/
RankingList::~RankingList()
{
}

/*INICJALIZACJA LISTY RANKINGOWEJ*/
vector<Record> RankingList::list{};

/*DODANIE KOLEJNEGO REKORDU WED£UG ODPOWIEDNIEJ KOLEJNOŒCI*/
void RankingList::add(const Record r)
{
	if (list.size() == 0) {
		list.push_back(r);
	}
	else {
		for (int i = 0; i < list.size(); i++) {
			//ISTNIEJE JUZ TAKI REKORD
			if (list[i].get_move() == r.get_move() && list[i].get_time() == r.get_time()){
				if (list[i].get_p1() != r.get_p1() || list[i].get_p2() != r.get_p2()) {
					list.insert(list.begin() + i, r);
				}
				return;
			}
			//DODANIE ZA WEDLUG CZASU
			if (list[i].get_move() == r.get_move() && list[i].get_time() >= r.get_time()) {
				list.insert(list.begin() + i, r);
				return;
			}

			//DODANIE PRZED
			if (list[i].get_move() > r.get_move()) {
				list.insert(list.begin() + i, r);
				return;
			}
		}
		//DODANIE NA KONIEC
		list.push_back(r);
	}
}

/*AKTUALIZACJA RANKINGU DANYMI Z PLIKU*/
void RankingList::loadFile()
{
	ifstream Plik("ranking.txt", ifstream::in);

	Record temp;
	while (Plik >> temp) {
		add(temp);
	}
	Plik.close();
}

/*ZAPIS DO PLIKU LISTY RANKINGU*/
void RankingList::saveFile()
{
	ofstream Plik("ranking.txt", std::ios::trunc);

	for(int i = 0; i < list.size(); i++){
		Plik << list[i] << "\n";
	}
	Plik.close();
}

/*WYŒWIETLENIE RANKINGU W KONSOLI*/
void RankingList::display()
{
	cout << "Top 10 graczy" << "\n\t" << "Wygrany" << "\t" << "Przegrany" << "\t" << "Ruchy" << "\t" << "Czas" << "\n\n";
	for (int i = 0; i < (list.size() < 10 ? list.size() : 10); i++) {
		cout << i + 1 << "\t"
			<< list[i].get_p1() << "\t"
			<< list[i].get_p2() << "\t"
			<< list[i].get_move() << "\t"
			//<< list[i].get_time() << "\n" 
			<< ((list[i].get_time() / 60 < 10 ? "0" : "") 
				+ to_string(int(list[i].get_time() / 60)) 
				+ ":"
				+ (list[i].get_time() % 60 < 10 ? "0" : "") 
				+ to_string(list[i].get_time() % 60)) << "\n";
	}
}

/*NADPISANIE OPERATORA << DLA LISTY RANKINGOWEJ*/
ostream& operator<<(ostream& wy, RankingList& list)
{
	wy << "TOP 10 GRACZY" << "\n\t" << "Wygrany" << "\t" << "Przegrany" << "\t" << "Ruchy" << "\t" << "Czas" << "\n\n";
	for (int i = 0; i < (list.list.size() < 10 ? list.list.size() : 10); i++) {

		wy << i + 1 << ((i + 1) > 9 ? "" : " ") << "\t"
		<< list.list[i].get_p1() << "\t"
			<< list.list[i].get_p2() << "\t"
			<< list.list[i].get_move() << "\t"
			<< ((list.list[i].get_time() / 60 < 10 ? "0" : "")
				+ to_string(int(list.list[i].get_time() / 60))
				+ ":"
				+ (list.list[i].get_time() % 60 < 10 ? "0" : "")
				+ to_string(list.list[i].get_time() % 60)) << "\n";
	}
	return wy;
}
