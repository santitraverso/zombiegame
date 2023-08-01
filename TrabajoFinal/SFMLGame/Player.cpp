#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "CollisionManager.h"

Player::Player(int gameWidth, int gameHeight) : Entity("Player", gameWidth, gameHeight)
{
	texture.loadFromFile("Resources/Textures/player.png");
	setTexture(texture);
	speed = 200.f;
}

Player::~Player()
{
}

void Player::Init(RenderWindow* window)
{
	this->window = window;
	isInit = true;
	currentHP = maxHP;
	sf::Vector2f spriteCenter(this->getLocalBounds().width / 2.f, this->getLocalBounds().height / 2.f);
	this->setOrigin(spriteCenter);
	radius = 20;
}

void Player::Update(float deltaTime)
{
	if (!isInit) {
		return;
	}
	velocity = Vector2f();
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity.x = -speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x = speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		velocity.y = -speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		velocity.y = speed;
	}
	move(velocity * deltaTime);
	float xPos = Clamp(getPosition().x, 0.f, (float)screenWidth - texture.getSize().x);
	float yPos = Clamp(getPosition().y, 0.f, (float)screenHeight - texture.getSize().y);
	setPosition(xPos, yPos);
	HandleRotation();
}

void Player::HandleRotation() {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);

	sf::Vector2f targetVector(static_cast<float>(mousePosition.x) - this->getPosition().x,
		static_cast<float>(mousePosition.y) -  this->getPosition().y);

	float angle = static_cast<float>(std::atan2(targetVector.y, targetVector.x));
	angle = angle * 180.f / static_cast<float>(pi); 

	this->setRotation(angle); 
}

void Player::ResolveCollision(Vector2f displacement, Entity* other)
{
	//Si llega a cero vidas que muera
	if (other->GetName() == "Zombie") {
		other->Kill();
		currentHP--;
	}
}


void Player::OnMouseClick(int x, int y)
{
	Fire(x, y);
}

void Player::Fire(int x, int y)
{
	sf::Vector2f direction = sf::Vector2f(x, y) - getPosition();
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length; 
	Bullet* bullet = new Bullet(this->getPosition());
	bullet->Init(direction);
	CollisionManager::GetInstance()->AddEntity(bullet);
}