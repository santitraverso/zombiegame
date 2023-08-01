#pragma once
#include <iostream>
#include <list>

using namespace std;

class Entity; // Foward declaration

class EntityManager
{
private:
	static EntityManager* instance;
	std::list<Entity*> entities;
	EntityManager() {};

public:
	~EntityManager();
	static EntityManager* GetInstance() {
		if (instance == nullptr)
		{
			instance = new EntityManager();
		}
		return instance;
	}
	void UpdateEntities(float deltaTime);
	void AddEntity(Entity* entity);
	std::list<Entity*> GetEntities() { return entities; }
	void OnMouseClick(int x, int y);
};