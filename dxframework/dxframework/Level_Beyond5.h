#pragma once
#include "level_base.h"
class Level_Beyond5 :	public Level_Base
{
private:
	int enemyCount;
	short randColor;

public:
	Level_Beyond5(void);
	~Level_Beyond5(void);

	void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);

	// accessors and mutators
	void SetEnemyCount( int newEnemyCount ){ enemyCount = newEnemyCount; };

};

