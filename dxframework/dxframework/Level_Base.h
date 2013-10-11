#pragma once

#include "Enemy_RedGhost.h"
#include "Enemy_GreenGhost.h"
#include "Enemy_PurpleGhost.h"
#include "Enemy_YellowGhost.h"

#include <vector>
#include <random>

class Level_Base
{
protected:
	// List of enemies to be used
	std::vector<Enemy_Base*>		enemies;

	// level constraints
	float x1, x2, z1, z2;
	
public:
	Level_Base(void);
	~Level_Base(void);

	virtual void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	virtual void Update( float dt, Object_Player* player, gunType bulletColor);
	virtual void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);

	float RandomBinomial( float min, float max);
};
