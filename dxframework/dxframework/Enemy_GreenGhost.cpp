#include "Enemy_GreenGhost.h"


Enemy_GreenGhost::Enemy_GreenGhost(void)
{
}


Enemy_GreenGhost::~Enemy_GreenGhost(void)
{
}

<<<<<<< HEAD
void Enemy_GreenGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);
=======
void Enemy_GreenGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);
>>>>>>> origin/MartinezWorking

	// initialize the variables
	isDead = false;
	health = 125;
	attackPower = 5;
	defencePower = 30;
<<<<<<< HEAD

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
=======
	movement->setPosition( D3DXVECTOR4(-20, 1.0, 100, 0));

	// Initialize the 3D model of the enemy.
	textureName = "GreenGhostTexture.jpg";
	textureNumber = GreenGhost;
	meshName = "GreenGhost.x";
>>>>>>> origin/MartinezWorking
}