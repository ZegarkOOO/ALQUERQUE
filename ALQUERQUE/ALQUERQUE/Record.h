#pragma once
#include <iostream>

using namespace std;

class Record
{
private:
	string m_p1, m_p2; //nazwy graczy
	int move, time; //liczniki
public:
	Record(string p1 = "", string p2 = "", int m = 0, int t = 0);

	int get_move()const;
	int get_time()const;
	string get_p1()const;
	string get_p2()const;

	friend ostream& operator<<(ostream& wy, const Record& r);
	friend istream& operator>>(istream& we, Record& r);
};

