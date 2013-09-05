#include "Enemy_YellowGhost.h"


Enemy_YellowGhost::Enemy_YellowGhost(void)
{
}


Enemy_YellowGhost::~Enemy_YellowGhost(void)
{
}

<<<<<<< HEAD
void Enemy_YellowGhost::Init(IDirect3DDevice9* m_pD3DDevice)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice);
=======
void Enemy_YellowGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);
>>>>>>> origin/MartinezWorking

	// initialize the variables
	isDead = false;
	health = 150;
	attackPower = 15;
	defencePower = 25;
<<<<<<< HEAD

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "Dwarf.X");
=======
	movement->setPosition( D3DXVECTOR4(0, 1.0, 100, 0));

	// Initialize the 3D model of the enemy.
	textureName = "YellowGhostTexture.jpg";
	textureNumber = YellowGhost;
	meshName = "YellowGhost.x";
>>>>>>> origin/MartinezWorking
}