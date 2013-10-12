#include "Level_Manager.h"


Level_Manager::Level_Manager(void)
{
}


Level_Manager::~Level_Manager(void)
{
}

void Level_Manager::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender, hkpWorld* world)
{
	// set to local variables
	device = m_pD3DDevice;
	render = m_pRender;
	havokWorld = world;

	// initialize the first level
	tutorial = new Level_Tutorial();
	tutorial->Init( device, render);

	// set the level variables
	level = Tutorial;
	levelCount = 5;
	enemyCount = 10;
}

void Level_Manager::Update( float dt, Object_Player* player, gunType bulletColor)
{
	switch( level )
	{
	case Tutorial:
		{
			// update the tutorial
			tutorial->Update( dt, player, bulletColor );

			// if the tutorial is done then switch to level one
			if ( tutorial->LeveledClear() == true )
			 {
					levelOne = new Level_One();
					levelOne->Init( device, render);
					if( tutorial != NULL )
						delete tutorial;
					level = One;
				}
			break;
		}
	case One:
		{
			// update level one
			levelOne->Update( dt, player, bulletColor);

			// if the tutorial is done then switch to level two
			if ( levelOne->LeveledClear() == true )
			{
				levelTwo = new Level_Two();
				levelTwo->Init( device, render);
				if ( levelOne != NULL )
					delete levelOne;
				level = Two;
			}
			break;
		}
	case Two:
		{
			// update level two
			levelTwo->Update( dt, player, bulletColor);

			// if the tutorial is done then switch to level three
			if ( levelTwo->LeveledClear() == true )
			{
				levelThree = new Level_Three();
				levelThree->Init( device, render);
				if ( levelTwo != NULL )
					delete levelTwo;
				level = Three;
			}
			break;
		}
	case Three:
		{
			// update level three
			levelThree->Update( dt, player, bulletColor);

			// if the tutorial is done then switch to level four
			if ( levelThree->LeveledClear() == true )
			{
				levelFour = new Level_Four();
				levelFour->Init( device, render);
				if ( levelThree != NULL)
					delete levelThree;
				level = Four;
			}
			break;
		}
	case Four:
		{
			// update level four
			levelFour->Update( dt, player, bulletColor);

			// if the tutorial is done then switch to level five
			if ( levelFour->LeveledClear() == true )
			{
				levels5Beyond[levelCount] = new Level_Beyond5();
				levels5Beyond[levelCount]->SetEnemyCount( enemyCount );
				levels5Beyond[levelCount]->Init( device, render);
				if ( levelFour != NULL)
					delete levelFour;
				level = FiveBeyond;
			}
			break;
		}
	case FiveBeyond:
		{
			// update current level
			levels5Beyond[levelCount]->Update( dt, player, bulletColor);

			// if the enemies are killed go to the next level
			if ( levels5Beyond[levelCount]->LeveledClear() == true )
			{
				// increase the level count and the amount of enemies
				levelCount++;
				enemyCount += 3;
				levels5Beyond[levelCount] = new Level_Beyond5();
				levels5Beyond[levelCount]->SetEnemyCount( enemyCount );
				levels5Beyond[levelCount]->Init( device, render);

				if ( levels5Beyond[levelCount-1] != NULL )
					delete levels5Beyond[levelCount-1];
			}
			break;
		}
	};
}

void Level_Manager::Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat)
{
	switch( level )
	{
	case Tutorial:
		{
			tutorial->Render( hwnd, veiwMat, projMat);
			break;
		}
	case One:
		{
			levelOne->Render( hwnd, veiwMat, projMat);
			break;
		}
	case Two:
		{
			levelTwo->Render( hwnd, veiwMat, projMat);
			break;
		}
	case Three:
		{
			levelThree->Render( hwnd, veiwMat, projMat);
			break;
		}
	case Four:
		{
			levelFour->Render( hwnd, veiwMat, projMat);
			break;
		}
	case FiveBeyond:
		{
			levels5Beyond[levelCount]->Render( hwnd, veiwMat, projMat);
			break;
		}
	};
}