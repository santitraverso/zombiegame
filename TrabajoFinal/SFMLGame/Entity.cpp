#include "Entity.h"

Entity::Entity(std::string name) : Sprite()
{
	this->name = name;
	EntityManager::GetInstance()->AddEntity(this);
}

Entity::Entity(std::string name, int screenWidth, int screenHeight) : Sprite()
{
	this->name = name;
	EntityManager::GetInstance()->AddEntity(this);
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

Entity::~Entity()
{
}

void Entity::SetSpriteSize(float width, float height)
{
    float scaleX = width / this->getLocalBounds().width;
    float scaleY = height / this->getLocalBounds().height;

    this->setScale(scaleX, scaleY);
}

void Entity::Kill()
{
}

void Entity::OnMouseClick(int x, int y)
{
}
