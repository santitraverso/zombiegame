#pragma once
#include <vector>
#include "Score.h"

class HighScoreManager {
private:
    vector<Score*> scores;
public:
    HighScoreManager();
    ~HighScoreManager();
    void AddScore(string name, int points);
    void RemoveScore(string name);
    void ModifyScore(string name, string newName, int points);
    void SaveScoresToFile(string fileName);
    void LoadScoresFromFile(string fileName);
    void DisplayScores();
    vector<Score*> GetScores();
    string GetScoresAsString();
};