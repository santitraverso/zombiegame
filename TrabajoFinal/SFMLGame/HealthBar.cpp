#include "HealthBar.h"

const float entitySize = 40;
HealthBar::HealthBar(Player* player) : Entity("Health")
{
	this->player = player;
}

HealthBar::~HealthBar()
{
}

void HealthBar::Init() {
    float posHeart = 0;
    for (int i = 0; i < player->currentHP; i++) {
        Heart* heart = new Heart();
        heart->setPosition(posHeart, 0);
        heart->SetSpriteSize(entitySize, entitySize);
        hearts.push_back(heart);
        posHeart += entitySize;
    }
}

void HealthBar::Update(float deltaTime)
{
    
    for (int i = 0; i < hearts.size(); i++) {
        if (i >= player->currentHP) {
            hearts[i]->setColor(Color::Transparent);
        }
    }
}

void HealthBar::ResolveCollision(Vector2f displacement, Entity* other)
{
}
