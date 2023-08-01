#include "CollisionManager.h"
#include "Entity.h"

CollisionManager* CollisionManager::instance = nullptr;

CollisionManager::CollisionManager()
{

}

void CollisionManager::ResolveCollision(Entity* entityA, Entity* entityB)
{
	Vector2f positionA = entityA->getPosition();
	Vector2f positionB = entityB->getPosition();
	float radiusA = entityA->radius;
	float radiusB = entityB->radius;

	Vector2f diff = positionA - positionB;

	float squaredDistance = diff.x * diff.x + diff.y * diff.y;

	float squaredSumRadii = (radiusA + radiusB) * (radiusA + radiusB);

	if (squaredDistance <= squaredSumRadii)
	{
		float depth = sqrt(squaredSumRadii) - sqrt(squaredDistance);

		float length = sqrt(squaredDistance);
		Vector2f normal = Vector2f(diff.x / length, diff.y / length);

		Vector2f displacementA = normal * depth * 0.5f;
		Vector2f displacementB = -normal * depth * 0.5f;

		entityA->ResolveCollision(displacementA, entityB);
		entityB->ResolveCollision(displacementB, entityA);
	}
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void CollisionManager::UpdateCollisions()
{
	for (list<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		for (list<Entity*>::iterator otherIt = it; otherIt != entities.end(); otherIt++)
		{
			Entity* entity = *it;
			Entity* otherEntity = *otherIt;
			if (entity != otherEntity && entity->getGlobalBounds().intersects(otherEntity->getGlobalBounds()))
			{
				ResolveCollision(entity, otherEntity);
			}
		}
	}
}
