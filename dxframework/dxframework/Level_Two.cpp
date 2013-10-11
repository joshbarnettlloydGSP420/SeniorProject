#include "Level_Two.h"


Level_Two::Level_Two(void)
{
}


Level_Two::~Level_Two(void)
{
}

// Kitchen Level
void Level_Two::Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// set the constraints for the enemy spawn points
	// low values
	x1 = -20;
	z1 = 4.5;

	// high values
	x2 = 22.5;
	z2 = 49;

	// create 2 GREEN ghosts to appear 
	for ( int i = 0; i < 2; ++i)
	{
		enemies[i] = new Enemy_GreenGhost();
		enemies[i]->Init( m_pD3DDevice, m_pRender);

		
		float x = RandomBinomial( x1, x2);
		float z = RandomBinomial( z1, z2);

		// set their positions randomly in the KITCHEN
		enemies[i]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
	}

	// create 2 RED ghosts to appear 
	for ( int i = 2; i < 4; ++i)
	{
		enemies[i] = new Enemy_RedGhost();
		enemies[i]->Init( m_pD3DDevice, m_pRender);

		// set their positions randomly in the KITCHEN
		enemies[i]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
	}
}
