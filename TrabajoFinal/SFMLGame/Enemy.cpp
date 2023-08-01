#include "Enemy.h"
#include <random>

float MaxSpeed = 150.0f; 

Enemy::Enemy(int gameWidth, int gameHeight) : Entity("Zombie", gameWidth, gameHeight)
{
	texture.loadFromFile("Resources/Textures/zombie.png");
	setTexture(texture);
}

Enemy::~Enemy()
{
}

void Enemy::Init(Player* player,int x, int y)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(50, 200);

    float randomSpeed = dist(rng);

    MaxSpeed = randomSpeed;
    cout << randomSpeed << endl;
    this->player = player;
    Vector2f spriteCenter(this->getLocalBounds().width / 2.f, this->getLocalBounds().height / 2.f);
    this->setOrigin(spriteCenter);
    radius = 20;
    initialPosition.x = x;
    initialPosition.y = y;
    position.x = x;
    position.y = y;
    setPosition(x, y);
}

void Enemy::Update(float deltaTime)
{
    Vector2f direction = player->getPosition() - position;
    MoveToTarget(player->getPosition(), direction);
    HandleRotation(direction);
    position = position + velocity * deltaTime;
    setPosition(position);
}

void Enemy::ResolveCollision(Vector2f displacement, Entity* other)
{
}

void Enemy::MoveToTarget(Vector2f target, Vector2f direction) {
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction = direction / distance;
        velocity = direction * MaxSpeed;
    }
}

void Enemy::HandleRotation(Vector2f direction)
{
    float rotation = std::atan2(direction.y, direction.x) * 180.f / static_cast<float>(pi);
    this->setRotation(rotation);
}

void Enemy::Kill() {
    position = initialPosition;
}
