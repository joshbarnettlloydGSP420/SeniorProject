#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "Object_Base.h"
#include "Object_Player.h"
#include "Enemy_Base.h"

class EntityManager
{
public:

	// Variables
	std::vector<Object_Base*>		v_baseObjects;
	std::vector<Enemy_Base*>		v_Enemy_Base;

	int								numEmemies;
	int								numObjects;

	EntityManager(void);
	~EntityManager(void);

	void entityUpdates(float deltaTime);
	void collisionChecks(float deltaTime);

	void objVsBullet(float deltaTime, Object_Base* object, Object_Player* player);
	void enemyVsPlayer(float deltaTime, Object_Player* player);

	void addEnemyObject(Enemy_Base* Enemy);
	void addBaseObject(Object_Base* Object);
};

