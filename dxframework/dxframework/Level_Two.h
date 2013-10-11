#pragma once
#include "level_base.h"
class Level_Two :
	public Level_Base
{
public:
	Level_Two(void);
	~Level_Two(void);

	void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void Update( float dt, Object_Player* player, gunType bulletColor);
	void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);
};

