#include "Level_Base.h"


Level_Base::Level_Base(void)
{
}


Level_Base::~Level_Base(void)
{
}

void Level_Base::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{

}

void Level_Base::Update( float dt, Object_Player* player, gunType bulletColor)
{
	// Update all the ghosts that are created
	for ( int i = 0; i < enemies.size(); ++i)
	{
		if ( enemies[i]->GetIsDead() == false)
		{
			enemies[i]->Update( dt, player);
			enemies[i]->BulletCollision( dt, player, bulletColor);
		}
	}
}

void Level_Base::Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat)
{
	// Render all of the ghosts
	for ( int i = 0; i < enemies.size(); ++i)
	{
		if ( enemies[i]->GetIsDead() == false)
		{
			enemies[i]->Render( hwnd, veiwMat, projMat);
		}
	}
}

float Level_Base::RandomBinomial( float min, float max)
{
	float random = ((float) rand()) / (float) RAND_MAX;

	float range = max - min;  
	return (random*range) + min;
}