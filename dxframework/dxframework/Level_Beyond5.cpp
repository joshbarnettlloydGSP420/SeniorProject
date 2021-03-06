#include "Level_Beyond5.h"


Level_Beyond5::Level_Beyond5(void)
{
	// initialize a set counter in case one is not set
	enemyCount = 5;
	randColor = 1;
}


Level_Beyond5::~Level_Beyond5(void)
{
}

// Entire House
void Level_Beyond5::Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender, hkpWorld* world )
{
	// initialize the leveled cleared to false
	levelCleared = false;

	// set the constraints for the enemy spawn points
	// low values
	x1 = -60;
	z1 = -35;

	// high values
	x2 = 65;
	z2 = 49;

	enemies.resize( enemyCount );
	// create random enemies based off of counter
	for ( int i = 0; i < enemyCount; ++i)
	{
		// randomize the enemy color
		randColor = RandomBinomial( 1, 5 );

		// create ghost based on random color
		if ( randColor == 1)
			enemies[i] = new Enemy_GreenGhost();
		else if ( randColor == 2)
			enemies[i] = new Enemy_RedGhost();
		else if ( randColor == 3)
			enemies[i] = new Enemy_PurpleGhost();
		else
			enemies[i] = new Enemy_YellowGhost();

		// initialize the ghost
		enemies[i]->Init( m_pD3DDevice, m_pRender);
		enemies[i]->CreateHavokObject( world );

		float x = RandomBinomial( x1, x2);
		float z = RandomBinomial( z1, z2);

		// set their positions randomly in the DINING ROOM
		enemies[0]->SetPosition( D3DXVECTOR4( x, 0, z, 0));
	}

	currentRoom = NO_ROOM;
	level = 5;

	InitRooms();
}

void Level_Beyond5::InitRooms()
{
	House = new Room();

	House->roomPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	House->roomSize = D3DXVECTOR3(125.0f, 20.0f, 84.0f);

	enemiesDead = false;
	puzzleSolved = true;
}