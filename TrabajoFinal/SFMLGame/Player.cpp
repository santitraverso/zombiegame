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
	points = 0;
	font.loadFromFile("Resources/Fonts/arial.ttf");
	text = new Text();
	text->setFont(font);
	text->setString(to_string(points));
	text->setCharacterSize(40);
	text->setFillColor(Color::Red);
	sf::FloatRect textRect = text->getLocalBounds();
	float textWidth = text->getLocalBounds().width;
	float windowWidth = window->getSize().x;
	text->setPosition(windowWidth - textWidth - 20, 0);
	EntityManager::GetInstance()->AddTextEntity(text);
	highScoreManager = new HighScoreManager();
	highScoreManager->LoadScoresFromFile("high_scores.dat");
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
	float xPos = Clamp(getPosition().x, 0.f, (float)screenWidth - radius);
	float yPos = Clamp(getPosition().y, 0.f, (float)screenHeight - radius);
	setPosition(xPos, yPos);
	HandleRotation();
	text->setString(to_string(points));
	sf::FloatRect textRect = text->getLocalBounds();
	float textWidth = text->getLocalBounds().width;
	float windowWidth = window->getSize().x;
	text->setPosition(windowWidth - textWidth - 20, 0);
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
	if (other->GetName() == "Zombie") {
		other->Kill();
		currentHP--;
		if (currentHP <= 0) {
			Text* textOver = new Text();
			textOver->setFont(font);
			textOver->setString("YOU ARE DEAD");
			textOver->setCharacterSize(100);
			textOver->setFillColor(Color::Red);
			sf::FloatRect textRect = textOver->getLocalBounds();
			float textWidth = textOver->getLocalBounds().width;
			float windowWidth = window->getSize().x;
			textOver->setPosition(windowWidth - textWidth - 20, 0);
			EntityManager::GetInstance()->AddTextEntity(textOver);
			this->setColor(Color::Transparent);

			ShowHighScore();
		}
	}
}


void Player::ShowHighScore()
{
	highScoreManager->AddScore("You", points);
	Text* textScore = new Text();
	textScore->setFont(font);
	textScore->setString("High scores:");
	textScore->setCharacterSize(50);
	textScore->setFillColor(Color::Red);
	sf::FloatRect textRect = textScore->getLocalBounds();
	float textWidth = textScore->getLocalBounds().width;
	float windowWidth = window->getSize().x;
	textScore->setPosition(windowWidth/2, 100);
	EntityManager::GetInstance()->AddTextEntity(textScore);

	vector<Score*> scores = highScoreManager->GetScores();
	int height = 140;
	for (Score* score : scores) {
		Text* textScorePoints = new Text();
		textScorePoints->setFont(font);
		textScorePoints->setString(score->GetName() + ": " + to_string(score->GetPoints()));
		textScorePoints->setCharacterSize(40);
		textScorePoints->setFillColor(Color::Red);
		sf::FloatRect textRect = textScorePoints->getLocalBounds();
		float textWidth = textScorePoints->getLocalBounds().width;
		float windowWidth = window->getSize().x;
		textScorePoints->setPosition(windowWidth/2, height);
		EntityManager::GetInstance()->AddTextEntity(textScorePoints);
		height += 40;
	}
}


void Player::OnMouseClick(int x, int y)
{
	if (currentHP > 0) {
		Fire(x, y);
	}
}

void Player::AddPoints(int points)
{
	this->points += points;
}

void Player::Fire(int x, int y)
{
	sf::Vector2f direction = sf::Vector2f(x, y) - getPosition();
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= length; 
	Bullet* bullet = new Bullet(this->getPosition(), this);
	bullet->Init(direction);
	CollisionManager::GetInstance()->AddEntity(bullet);
}