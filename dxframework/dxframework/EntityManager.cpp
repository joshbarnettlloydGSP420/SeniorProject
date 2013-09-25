#include "EntityManager.h"


EntityManager::EntityManager(void)
{

}

EntityManager::~EntityManager(void)
{

}

void EntityManager::entityUpdates(float deltaTime)
{

}

void EntityManager::collisionChecks(float deltaTime)
{

}

void EntityManager::objVsPlayer(float deltaTime, Object_Player* player)
{

}

void EntityManager::enemyVsPlayer(float deltaTime, Object_Player* player)
{
	if(!player->beenHit)
	{
		for(short i = 0; i < v_Enemy_Base.max_size(); ++i)
		{
			if(v_Enemy_Base.at(i)->CollisionDetection(player->objectBody->getRigidBody()))
			{
				player->health -= 2;
				player->hitTimer = 0.0f;
			}
		}
	}
}

void EntityManager::addEnemyObject(Enemy_Base* Enemy)
{

}

void EntityManager::addBaseObject(Object_Base* Object)
{
	
}