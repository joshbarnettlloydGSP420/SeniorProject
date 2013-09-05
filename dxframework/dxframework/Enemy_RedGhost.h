#pragma once
#include "Enemy_Base.h"

class Enemy_RedGhost : public Enemy_Base
{
public:
	Enemy_RedGhost(void);
	~Enemy_RedGhost(void);

<<<<<<< HEAD
	void Init(IDirect3DDevice9* m_pD3DDevice);
=======
	void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
>>>>>>> origin/MartinezWorking
};

