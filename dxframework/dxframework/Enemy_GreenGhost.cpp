#include "Enemy_GreenGhost.h"


Enemy_GreenGhost::Enemy_GreenGhost(void)
{
}


Enemy_GreenGhost::~Enemy_GreenGhost(void)
{
}

void Enemy_GreenGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);

	// initialize the variables
	isDead = false;
	health = 125;
	attackPower = 5;
	defencePower = 30;

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
}