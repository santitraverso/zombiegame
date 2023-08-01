#include "Heart.h"

Heart::Heart() : Entity("Health")
{
	texture.loadFromFile("Resources/Textures/heart.png");
	setTexture(texture);
}

Heart::~Heart()
{
}


void Heart::Update(float deltaTime)
{
}

void Heart::ResolveCollision(Vector2f displacement, Entity* other)
{
}
