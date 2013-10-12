#pragma once
#include "level_base.h"
class Level_One :	public Level_Base
{
private:
public:
	Level_One(void);
	~Level_One(void);

	void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	void InitRooms();
	void Update( float dt, Object_Player* player, gunType bulletColor);
	void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);
};

