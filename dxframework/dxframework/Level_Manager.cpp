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

	level = Tutorial;
	levelCount = 5;

}

void Level_Manager::Update( float dt, Object_Player* player, gunType bulletColor)
{
	switch( level )
	{
	case Tutorial:
		{
			// update the tutorial
			tutorial->Update( dt, player, bulletColor );

			// TODO:  if the tutorial is done then switch to level one
			// the door is open is the switch

			// if ()
			// {
			//		levelOne = new Level_One();
			//		levelOne->Init( device, render);
			//		if( tutorial != NULL )
			//			delete tutorial;
			//		level = One;
			//	}
			break;
		}
	case One:
		{
			levelOne->Update( dt, player, bulletColor);

			// TODO: if the enemies are killed and the door is open go to level 2
			//if ()
			//{
			//	levelTwo = new LevelTwo();
			//	levelTwo->Init( device, render);
			//	if ( levelOne != NULL )
			//		delete levelOne;
			//	level = Two;
			//}
			break;
		}
	case Two:
		{
			levelTwo->Update( dt, player, bulletColor);

			// TODO:  if the enemies are killed and the door is open go to level 3

			//if ()
			//{
			//	levelThree = new LevelThree();
			//	levelThree->Init( device, render);
			//	if ( levelTwo != NULL )
			//		delete levelTwo;
			//	level = Three;
			//}
			break;
		}
	case Three:
		{
			levelThree->Update( dt, player, bulletColor);

			// TODO: if the enemies are killed and the door is open go to level 4

			//if ()
			//{
			//	levelFour = new LevelFour();
			//	levelFour->Init( device, render);
			//	if ( levelThree != NULL)
			//		delete LevelThree;
			//	level = Four;
			//}
			break;
		}
	case Four:
		{
			levelFour->Update( dt, player, bulletColor);

			// TODO:  if the enemies are killed go to level 5

			//if ()
			//{
			//	levels5Beyond[levelCount] = new Level_Beyond5();
			//	levels5Beyond[levelCount]->Init( device, render);
			//	if ( levelFour != NULL)
			//		delete levelFour;
			//	level = FiveBeyond;
			//}
			break;
		}
	case FiveBeyond:
		{

			levels5Beyond[levelCount]->Update( dt, player, bulletColor);

			// TODO:  if the enemies are killed go to the next level
			if ()
			{
				levels5Beyond[levelCount] = new Level_Beyond5();
				levels5Beyond[levelCount]->Init( device, render);
				if ( levels5Beyond[levelCount-1] != NULL )
					delete levels5Beyond[levelCount-1];
				levelCount++;
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