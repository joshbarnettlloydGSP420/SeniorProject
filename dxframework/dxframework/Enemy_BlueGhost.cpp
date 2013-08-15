#include "Enemy_BlueGhost.h"


Enemy_BlueGhost::Enemy_BlueGhost(void)
{
}


Enemy_BlueGhost::~Enemy_BlueGhost(void)
{
}

void Enemy_BlueGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);

	// initialize the variables
	isDead = false;
	health = 100;
	attackPower = 10;
	defencePower = 20;

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
}