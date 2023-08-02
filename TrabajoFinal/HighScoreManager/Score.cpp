#include "Score.h"

Score::Score()
{
	name = "Test";
	points = 0;
}

Score::Score(string name, int points)
{
	this->name = name;
	this->points = points;
}

Score::~Score()
{
}

string Score::Print()
{
	return string();
}

string Score::GetName()
{
	return name;
}

int Score::GetPoints()
{
	return points;
}

void Score::SetPoints(int points)
{
	this->points = points;
}

void Score::SetName(string name)
{
	this->name = name;
}
