#pragma once
#include <list>
#include <iostream>

using namespace std;

class Entity;

class CollisionManager
{
private:
	static CollisionManager* instance;
	list<Entity*> entities;
	CollisionManager();
	void ResolveCollision(Entity* entityA, Entity* entityB);
public:
	virtual ~CollisionManager();
	static CollisionManager* GetInstance() {
		if (instance == nullptr)
		{
			instance = new CollisionManager();
		}
		return instance;
	}
	void AddEntity(Entity* entity);
	void UpdateCollisions();
};

