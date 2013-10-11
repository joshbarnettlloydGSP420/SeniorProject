#include "Level_One.h"


Level_One::Level_One(void)
{
}


Level_One::~Level_One(void)
{
}

// Dining Room Level
void Level_One::Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// set the constraints for the enemy spawn points
	// low values
	x1 = 22.5;
	z1 = -35;

	// high values
	x2 = 65;
	z2 = 49;

	// create 4 GREEN ghosts to appear 
	for ( int i = 0; i < 4; ++i)
	{
		enemies[i] = new Enemy_GreenGhost();
		enemies[i]->Init( m_pD3DDevice, m_pRender);

		float x = RandomBinomial( x1, x2);
		float z = RandomBinomial( z1, z2);

		// set their positions randomly in the DINING ROOM
		enemies[i]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
	}
}