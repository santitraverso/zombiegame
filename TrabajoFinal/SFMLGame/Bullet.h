#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Player.h"
#include "Utils.h"

using namespace sf;

class Bullet : public Entity
{
private:
	Texture texture;
	float speed;
	Vector2f velocity;
	Vector2f position;
	int radius;
	Player* player;
public:
	Bullet(Vector2f pos, Player* player);
	virtual ~Bullet();
	void Update(float deltaTime) override;
	virtual void ResolveCollision(Vector2f displacement, Entity* other);
	void Init(Vector2f direction);
};

