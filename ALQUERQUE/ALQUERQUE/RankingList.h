#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Record.h"

using namespace std;

class RankingList
{
private:
	static vector <Record> list; //lista 

public:
	RankingList();
	~RankingList();

	void add(const Record r);
	void loadFile();
	void saveFile();
	void display();

	friend ostream& operator<<(ostream& wy, RankingList& list);

};

