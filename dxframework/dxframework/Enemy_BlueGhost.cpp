#include "Enemy_BlueGhost.h"


Enemy_BlueGhost::Enemy_BlueGhost(void)
{
}


Enemy_BlueGhost::~Enemy_BlueGhost(void)
{
}

<<<<<<< HEAD
void Enemy_BlueGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);
=======
void Enemy_BlueGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);
>>>>>>> origin/MartinezWorking

	// initialize the variables
	isDead = false;
	health = 100;
	attackPower = 10;
	defencePower = 20;
<<<<<<< HEAD

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
=======
	movement->setPosition( D3DXVECTOR4(20, 1.0, 100, 0));

	// Initialize the 3D model of the enemy.
	textureName = "BlueGhostTexture.jpg";
	textureNumber = BlueGhost;
	meshName = "BlueGhost.x";
>>>>>>> origin/MartinezWorking
}