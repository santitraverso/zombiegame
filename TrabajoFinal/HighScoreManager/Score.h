#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Score {
private:
	string name;
	int points;
public:
	Score();
	Score(string name, int points);
	~Score();
	string Print();
	string GetName();
	int GetPoints();
	void SetPoints(int points);
	void SetName(string name);
};