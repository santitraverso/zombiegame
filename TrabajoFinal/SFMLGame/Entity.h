#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Utils.h"

using namespace sf;

class Entity : public Sprite
{
private:
	string name;
protected:
	int screenWidth;
	int screenHeight;
public:
	float radius;
	Entity(string name);
	Entity(string name, int screenWidth, int screenHeight);
	virtual ~Entity();
	string GetName() { return name; };
	virtual void Update(float deltaTime) = 0;
	virtual void ResolveCollision(Vector2f displacement, Entity* other) = 0;
	void SetSpriteSize(float width, float height);
	virtual void Kill();
	virtual void OnMouseClick(int x, int y);
};

