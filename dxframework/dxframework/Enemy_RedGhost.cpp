#include "Enemy_RedGhost.h"


Enemy_RedGhost::Enemy_RedGhost(void)
{
}

Enemy_RedGhost::~Enemy_RedGhost(void)
{
}

<<<<<<< HEAD
void Enemy_RedGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);
=======
void Enemy_RedGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);
>>>>>>> origin/MartinezWorking

	// initialize the variables
	isDead = false;
	health = 200;
	attackPower = 20;
	defencePower = 10;
<<<<<<< HEAD

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
=======
	movement->setPosition( D3DXVECTOR4(10, 1.0, 50, 0));

	// Initialize the 3D model of the enemy.
	textureName = "RedGhostTexture.jpg";
	textureNumber = RedGhost;
	meshName = "RedGhost.x";
>>>>>>> origin/MartinezWorking
}