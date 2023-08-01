#include "Bullet.h"

Bullet::Bullet(Vector2f pos) : Entity("Bullet")
{
	texture.loadFromFile("Resources/Textures/bullet.png");
	setTexture(texture);
	speed = 700.f;
	position = pos;
	setPosition(pos);
	radius = 20;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float deltaTime)
{
	position = position + velocity * deltaTime;
	setPosition(position);
}

void Bullet::ResolveCollision(Vector2f displacement, Entity* other)
{
	if (other->GetName() == "Zombie") {
		other->Kill();
		position.x = 9999;
		position.y = 9999;
	}
}

void Bullet::Init(Vector2f direction)
{
	velocity = direction * speed;
	SetSpriteSize(radius, radius);
}
