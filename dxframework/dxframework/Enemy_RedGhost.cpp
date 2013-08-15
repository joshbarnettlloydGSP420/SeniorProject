#include "Enemy_RedGhost.h"


Enemy_RedGhost::Enemy_RedGhost(void)
{
}

Enemy_RedGhost::~Enemy_RedGhost(void)
{
}

void Enemy_RedGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);

	// initialize the variables
	isDead = false;
	health = 200;
	attackPower = 20;
	defencePower = 10;

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
}