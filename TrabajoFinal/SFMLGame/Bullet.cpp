#include "Bullet.h"

Bullet::Bullet(Vector2f pos, Player* player) : Entity("Bullet")
{
	texture.loadFromFile("Resources/Textures/bullet.png");
	setTexture(texture);
	speed = 700.f;
	position = pos;
	setPosition(pos);
	radius = 20;
	this->player = player;
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
		player->AddPoints(other->points);
		position.x = 9999;
		position.y = 9999;
		speed = 0.f;
	}
}

void Bullet::Init(Vector2f direction)
{
	velocity = direction * speed;
	SetSpriteSize(radius, radius);
}
