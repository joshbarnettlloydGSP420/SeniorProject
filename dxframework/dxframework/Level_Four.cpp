#include "Level_Four.h"


Level_Four::Level_Four(void)
{
}


Level_Four::~Level_Four(void)
{
}

// Foyer Level
void Level_Four::Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// set the constraints for the enemy spawn points
	// low values
	x1 = -20;
	z1 = -35;

	// high values
	x2 = 22.5;
	z2 = 4.5;

	// create 1 GREEN ghosts to appear 
	enemies[0] = new Enemy_GreenGhost();
	enemies[0]->Init( m_pD3DDevice, m_pRender);

	float x = RandomBinomial( x1, x2);
	float z = RandomBinomial( z1, z2);

	// set their positions randomly in the FOYER
	enemies[0]->SetPosition( D3DXVECTOR4( x, 0, z, 0));

	// create 1 RED ghosts to appear 
	enemies[1] = new Enemy_RedGhost();
	enemies[1]->Init( m_pD3DDevice, m_pRender);

	float x = RandomBinomial( x1, x2);
	float z = RandomBinomial( z1, z2);

	// set their positions randomly in the FOYER
	enemies[1]->SetPosition( D3DXVECTOR4( x, 0, z, 0));

	// create 1 PURPLE ghosts to appear 
	enemies[2] = new Enemy_PurpleGhost();
	enemies[2]->Init( m_pD3DDevice, m_pRender);

	float x = RandomBinomial( x1, x2);
	float z = RandomBinomial( z1, z2);

	// set their positions randomly in the FOYER
	enemies[2]->SetPosition( D3DXVECTOR4( x, 0, z, 0));

	// create 1 YELLOW ghosts to appear 
	enemies[3] = new Enemy_YellowGhost();
	enemies[3]->Init( m_pD3DDevice, m_pRender);

	float x = RandomBinomial( x1, x2);
	float z = RandomBinomial( z1, z2);

	// set their positions randomly in the FOYER
	enemies[3]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
}