#pragma once
#include "Enemy_Base.h"
class Enemy_BlueGhost : public Enemy_Base
{
public:
	Enemy_BlueGhost(void);
	~Enemy_BlueGhost(void);

	void Init( IDirect3DDevice9* m_pD3DDevice);
};

