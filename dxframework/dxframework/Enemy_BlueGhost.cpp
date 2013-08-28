#include "Enemy_BlueGhost.h"


Enemy_BlueGhost::Enemy_BlueGhost(void)
{
}


Enemy_BlueGhost::~Enemy_BlueGhost(void)
{
}

void Enemy_BlueGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);

	// initialize the variables
	isDead = false;
	health = 100;
	attackPower = 10;
	defencePower = 20;
	movement->setPosition( D3DXVECTOR4(20, 1.0, 100, 0));

	// Initialize the 3D model of the enemy.
	textureName = "BlueGhostTexture.jpg";
	textureNumber = BlueGhost;
	meshName = "BlueGhost.x";
}