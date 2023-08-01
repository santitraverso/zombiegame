#pragma once
#include "Entity.h"
#include "Player.h"
class Enemy : public Entity
{
private:
	Texture texture;
	Vector2f velocity;
	Player* player;
	Vector2f position;
	Vector2f initialPosition;
public:
	Enemy(int gameWidth, int gameHeight);
	~Enemy();
	void Init(Player* player, int x, int y);
	void Update(float deltaTime) override;
	virtual void ResolveCollision(Vector2f displacement, Entity* other);
	void MoveToTarget(Vector2f target, Vector2f direction);
	void HandleRotation(Vector2f direction);
	void Kill() override;
};

