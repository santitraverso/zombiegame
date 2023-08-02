#include "HighScoreManager.h"
#include <algorithm>
using namespace std;

HighScoreManager::HighScoreManager()
{
}

HighScoreManager::~HighScoreManager()
{
}

void HighScoreManager::AddScore(string name, int points)
{
	Score* score = new Score(name, points);
	scores.push_back(score);
}

void HighScoreManager::RemoveScore(string name)
{
	auto scoreToRemove = std::remove_if(scores.begin(), scores.end(),
		[&name](Score* score) { return score->GetName() == name; });
	scores.erase(scoreToRemove, scores.end());
}

void HighScoreManager::ModifyScore(string name, string newName, int points)
{
	auto scoreToModify = std::find_if(scores.begin(), scores.end(),
		[&name](Score* score) { return score->GetName() == name; });
	if (scoreToModify != scores.end()) {
		(*scoreToModify)->SetPoints(points);
		(*scoreToModify)->SetName(newName);
	}
}

void HighScoreManager::SaveScoresToFile(string fileName) {

	ofstream outFile(fileName, std::ios::binary);
	if (outFile.is_open()) {
		for (Score* score : scores) {
			size_t size = score->GetName().size();
			outFile.write((char*) & size, sizeof(size));
			outFile.write((char*)&(score->GetName()[0]), size);
		
			int points = score->GetPoints();
			outFile.write(reinterpret_cast<const char*>(&points), sizeof(int));
		}
		outFile.close();
	}
}

void HighScoreManager::LoadScoresFromFile(string fileName) {
	ifstream inFile(fileName, ios::binary);
	if (inFile.is_open()) {
		scores.clear();
		size_t size;
		while (inFile.read(reinterpret_cast<char*>(&size), sizeof(size))) {
			char* nameBuffer = new char[size];
			inFile.read(nameBuffer, size);
			string name(nameBuffer, size);
			delete[] nameBuffer;

			int points;
			inFile.read(reinterpret_cast<char*>(&points), sizeof(int));

			scores.push_back(new Score(name, points));
		}
		inFile.close();
	}
}

void HighScoreManager::DisplayScores() {
	sort(scores.begin(), scores.end());
	cout << "High Scores:" << std::endl;
	for (Score* score : scores) {
		cout << score->GetName() << ": " << score->GetPoints() << endl;
	}
}

bool HighScoreManager::CompareScores(Score* score1, Score* score2) {
	return score1->GetPoints() > score2->GetPoints();
}