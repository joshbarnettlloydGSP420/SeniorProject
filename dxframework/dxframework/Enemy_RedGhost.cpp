#include "Enemy_RedGhost.h"


Enemy_RedGhost::Enemy_RedGhost(void)
{
}

Enemy_RedGhost::~Enemy_RedGhost(void)
{
}

void Enemy_RedGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);

	// initialize the variables
	isDead = false;
	health = 200;
	attackPower = 20;
	defencePower = 10;

	// Initialize the 3D model of the enemy.
	textureName = "RedGhostTexture.jpeg";
	textureNumber = RedGhost;
	meshName = "Dwarf.x";
}