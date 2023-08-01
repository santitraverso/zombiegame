#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	Texture texture;
	Vector2f velocity;
	float speed;
	RenderWindow* window;
	bool isInit = false;
public:
	int currentHP;
	int maxHP = 5;
	Player(int screenWidth, int screenHeight);
	~Player();
	void Init(RenderWindow* window);
	void Update(float deltaTime) override;
	void ResolveCollision(Vector2f displacement, Entity* other) override;
	void Fire(int x, int y);
	void OnMouseClick(int x, int y);
private:
	void HandleRotation();
};

