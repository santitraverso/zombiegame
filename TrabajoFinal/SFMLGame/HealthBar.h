#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Player.h"
#include "Utils.h"
#include "Heart.h"

using namespace sf;

class HealthBar : public Entity
{
private:
	vector<Heart*> hearts;
	Player* player;
public:
	HealthBar(Player* player);
	virtual ~HealthBar();
	void Init();
	void Update(float deltaTime) override;
	virtual void ResolveCollision(Vector2f displacement, Entity* other);
};

