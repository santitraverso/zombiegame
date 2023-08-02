#pragma once
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Entity; // Foward declaration

class EntityManager
{
private:
	static EntityManager* instance;
	list<Entity*> entities;
	list<Text*> textEntities;
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
	list<Entity*> GetEntities() { return entities; }
	list<Text*> GetTextEntities() { return textEntities; }
	void OnMouseClick(int x, int y);
	void AddTextEntity(Text* text);
};