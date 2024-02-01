#include "Record.h"

/*KONSTRUKTOR Z LISTA INICJALIZUJ¥C¥*/
Record::Record(string p1, string p2, int m, int t) : m_p1{p1}, m_p2{p2}, move{m}, time{t}
{
}

/*ZWRACA LICZNIK RUCHÓW*/
int Record::get_move()const
{
	return move;
}

/*ZWRACA LICZNIK CZASU*/
int Record::get_time()const
{
	return time;
}

/*ZWRACA NAZWÊ 1 GRACZA*/
string Record::get_p1() const
{
	return this->m_p1;
}

/*ZWRACA NAZWÊ 2 GRACZA*/
string Record::get_p2() const
{
	return this->m_p2;
}

/*PRZE£ADOWANIE OPERATORA WYJŒCIA */
ostream& operator<<(ostream& wy, const Record& r)
{
	wy << r.m_p1 << "\t" << r.m_p2 << "\t" << r.move << "\t" << r.time;
	return wy;
}

/*PRZE£ADOWANIE OPERATORA WEJŒCIA */
istream& operator>>(istream& we, Record& r)
{
	return we >> r.m_p1 >> r.m_p2 >> r.move >> r.time;
}
