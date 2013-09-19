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
	std::vector<Object_Player*>		v_playerObjects;
	std::vector<Enemy_Base*>		v_Enemy_Base;

	EntityManager(void);
	~EntityManager(void);

	void entityUpdates(float deltaTime);
	void collisionChecks(float deltaTime);

	void objVsPlayer(float deltaTime);
	void enemyVsPlayer(float deltaTime);
};

