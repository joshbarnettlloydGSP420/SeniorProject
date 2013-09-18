#include "Enemy_YellowGhost.h"


Enemy_YellowGhost::Enemy_YellowGhost(void)
{
}


Enemy_YellowGhost::~Enemy_YellowGhost(void)
{
}

void Enemy_YellowGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);

	// initialize the variables
	isDead = false;
	health = 150;
	attackPower = 15;
	defencePower = 25;
	movement->setPosition( D3DXVECTOR4(0, 1.0, 100, 0));

	// Initialize the 3D model of the enemy.
	textureName = L"YellowGhostTexture.jpg";
	textureNumber = YellowGhost;
	meshName = L"YellowGhost.x";
}