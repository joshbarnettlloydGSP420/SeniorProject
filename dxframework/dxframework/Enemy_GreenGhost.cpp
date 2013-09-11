#include "Enemy_GreenGhost.h"


Enemy_GreenGhost::Enemy_GreenGhost(void)
{
}


Enemy_GreenGhost::~Enemy_GreenGhost(void)
{
}

void Enemy_GreenGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);

	// initialize the variables
	isDead = false;
	health = 125;
	attackPower = 5;
	defencePower = 30;

	// Initialize the 3D model of the enemy.
	textureName = "GreenGhostTexture.jpeg";
	textureNumber = GreenGhost;
	meshName = "Dwarf.x";
}