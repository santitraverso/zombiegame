#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Heart.h"
#include "CollisionManager.h"
#include <vector>

using namespace sf;

class Game {
private:
	bool isRunning;
	void _Update(float deltaTime);
	void _Draw();
	int maxEnemies = 20;
	Player* player;
	RenderWindow* window;
	vector<Enemy*> enemies;
public:
	Game();
	virtual ~Game();
	void Run();
	void CreateEnemies();
};