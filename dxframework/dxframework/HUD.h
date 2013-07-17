#pragma once
#pragma comment(lib, "winmm.lib")
//////////////////////////////////////////////////////////////////////////
// Direct3D 9 headers and libraries required
//////////////////////////////////////////////////////////////////////////
#include "InputManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "Timer.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
class HUD
{
private:
	//pacman variables
	int score;
	int highScore;
	int lives;
	int level;
	bool hudOn;

	char seconds[30];
	char hudPrint[30];

	RECT scoreRect, highScoreRect, timeRect, livesRect, levelRect;
	
	//timer
	CTimer* timer;
	float currentTime;
	float previousTime;

	ID3DXFont*	font;			// Font Object
	InputManager* myInput;

public:
	HUD(void);
	~HUD(void);

	void Init(IDirect3DDevice9* m_pD3DDevice, InputManager* input);

	void Update(float dt);

	void Render();

	void Shutdown();
};

