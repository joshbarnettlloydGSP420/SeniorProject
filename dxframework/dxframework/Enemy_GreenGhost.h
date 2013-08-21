#pragma once
#include "Enemy_Base.h"

class Enemy_GreenGhost : public Enemy_Base
{
public:
	Enemy_GreenGhost(void);
	~Enemy_GreenGhost(void);

	void Init( IDirect3DDevice9* m_pD3DDevice);
};

