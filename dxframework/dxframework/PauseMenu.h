#pragma once

#include "BaseMenu.h"

class PauseMenu :  public BaseMenu
{
private:
	////////////////////////////////////////////////////////////////////////
	// Pause Menu specific enum
	////////////////////////////////////////////////////////////////////////
	enum PAUSE_MENU_STATE
	{
		p_PAUSE_MENU	= 0,
		p_RESUME_GAME	= 1,
		p_RESTART		= 2,
		p_MAIN_MENU		= 3
	}pauseState;

public:
	PauseMenu();
	~PauseMenu(void);
	void DrawBackground();
	virtual void Render();
	virtual void Update();
	bool Init(InputManager* input, IDirect3DDevice9*	m_pD3DDevice);
	// Accessors and Mutators
	int GetState() { return pauseState; };
};

