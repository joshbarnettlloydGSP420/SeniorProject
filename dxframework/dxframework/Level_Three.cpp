#include "Level_Three.h"


Level_Three::Level_Three(void)
{
}


Level_Three::~Level_Three(void)
{
}

// Ball Room Level
void Level_Three::Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// set the constraints for the enemy spawn points
	// low values
	x1 = -60;
	z1 = -35;

	// high values
	x2 = -20;
	z2 = 49;

	// create 2 PURPLE ghosts to appear 
	for ( int i = 0; i < 2; ++i)
	{
		enemies[i] = new Enemy_PurpleGhost();
		enemies[i]->Init( m_pD3DDevice, m_pRender);

		float x = RandomBinomial( x1, x2);
		float z = RandomBinomial( z1, z2);

		// set their positions randomly in the BALL ROOM
		enemies[i]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
	}

	// create 1 RED ghost
	enemies[2] = new Enemy_PurpleGhost();
	enemies[2]->Init( m_pD3DDevice, m_pRender);

	float x = RandomBinomial( x1, x2);
	float z = RandomBinomial( z1, z2);

	// set their positions randomly in the BALL ROOM
	enemies[2]->SetPosition( D3DXVECTOR4( x, 0, z, 0));

	// create 1 GREEN ghost
	enemies[3] = new Enemy_PurpleGhost();
	enemies[3]->Init( m_pD3DDevice, m_pRender);

	float x = RandomBinomial( x1, x2);
	float z = RandomBinomial( z1, z2);

	// set their positions randomly in the BALL ROOM
	enemies[3]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
}