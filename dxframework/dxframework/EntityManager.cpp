#include "EntityManager.h"


EntityManager::EntityManager(void)
{

}

EntityManager::~EntityManager(void)
{

}

void EntityManager::entityUpdates(float deltaTime, Object_Player* Player)
{

}

void EntityManager::collisionChecks(float deltaTime, Object_Player* Player)
{

}

bool EntityManager::objVsBullet(float deltaTime, Object_Base* object, Object_Player* player)
{
	hkAabb aabbBase;
	hkAabb aabbOut;

	// Object Hit Bullets
	for(short i = 0; i < ARRAYSIZE(player->bull); ++i)
	{
		object->rigidBody->getCollidable()->getShape()->getAabb(object->rigidBody->getTransform(), 0.4f, aabbOut);
		player->bull[i].bulletObject->getCollidable()->getShape()->getAabb(player->bull[i].bulletObject->getTransform(), 0.4f, aabbBase);


		if(aabbBase.overlaps(aabbOut))
		{
			return true;
		}

		return false;
	}
}

bool EntityManager::objVsPlayer(float deltaTime, Object_Base* object, Object_Player* player)
{
	// Object Hit Bullets
	
	hkAabb aabbBase;
	hkAabb aabbOut;

	object->rigidBody->getCollidable()->getShape()->getAabb(object->rigidBody->getTransform(), 0.4f, aabbOut);
	player->objectBody->getRigidBody()->getCollidable()->getShape()->getAabb(player->objectBody->getRigidBody()->getTransform(), 0.4f, aabbBase);


	if(aabbBase.overlaps(aabbOut))
	{
		return true;
	}

	return false;
}

bool EntityManager::enemyVsBullet(float deltaTime, Enemy_Base* enemy, Object_Player* player)
{
	// Enemy Hits Bullets
	for(short i = 0; i < ARRAYSIZE(player->bull); ++i)
	{
		if(player->mPSys->getmAliveParticles().at(i))
		{
			if(enemy->CollisionDetection(player->bull[i].bulletObject))
			{
				player->bull[i].isAlive = false;
				return true;
			}
		}
	}

	return false;
}

bool EntityManager::enemyVsPlayer(float deltaTime, Enemy_Base* enemy,  Object_Player* player)
{
	// Enemy Hits Player
	if(!player->beenHit)
	{
		for(short i = 0; i < v_Enemy_Base.max_size(); ++i)
		{
			if(enemy->CollisionDetection(player->objectBody->getRigidBody()))
			{
				return true;
			}
		}
	}

	return false;
}

//void EntityManager::addEnemyObject(Enemy_Base* Enemy)
//{
//	v_Enemy_Base.push_back(Enemy);
//}
//
//void EntityManager::addBaseObject(Object_Base* Object)
//{
//	v_baseObjects.push_back(Object);
//}