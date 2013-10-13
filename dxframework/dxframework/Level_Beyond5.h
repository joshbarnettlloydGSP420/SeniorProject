#pragma once
#include "level_base.h"
class Level_Beyond5 :	public Level_Base
{
private:
	int enemyCount;
	short randColor;

	// constraints for the house, when looking from the imaginary front door.
	float		backWall;
	float		frontWall;
	float		leftWall;
	float		rightWall;

public:
	Level_Beyond5(void);
	~Level_Beyond5(void);

	void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);

	// accessors and mutators
	void SetEnemyCount( int newEnemyCount ){ enemyCount = newEnemyCount; };

};
