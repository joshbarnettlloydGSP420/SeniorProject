#pragma once
#include "level_base.h"
class Level_Three :	public Level_Base
{
public:
	Level_Three(void);
	~Level_Three(void);

	void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender, hkpWorld* world );
	void InitRooms();

	void SetEnemyCount( float enemyCount);
};

