#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Player.h"
#include "Utils.h"

using namespace sf;

class Heart : public Entity
{
private:
	Texture texture;
public:
	Heart();
	virtual ~Heart();
	void Update(float deltaTime) override;
	virtual void ResolveCollision(Vector2f displacement, Entity* other);
};

