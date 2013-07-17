#include "HUD.h"


HUD::HUD(void)
{
}


HUD::~HUD(void)
{
}

void HUD::Init( IDirect3DDevice9* m_pD3DDevice, InputManager* input )
{
	// set the input
	myInput = input;

	//pacman hud
	score = 0;
	highScore = 10000;
	lives = 3;
	level = 1;
	hudOn = true;

	//rects to reference position
	SetRect(&scoreRect, 0, 0, 800, 600);
	SetRect(&highScoreRect, 0, 0, 800, 600);
	SetRect(&timeRect, 0, 0, 800, 600);
	SetRect(&livesRect, 0, 0, 800, 600);
	SetRect(&levelRect, 0, 0, 800, 600);

	//timer
	timer = new CTimer();
	timer->Start();
	previousTime = currentTime = timer->GetRunningTime();

	// create a FONT object
	AddFontResourceEx("Delicious-Roman.otf", FR_PRIVATE, 0);
	D3DXCreateFont(m_pD3DDevice, 30, 0, FW_BOLD, 0, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Delicious-Roman"), 
		&font);
}

void HUD::Update(float dt)
{
	//update timer
	timer->Update();
	currentTime = timer->GetRunningTime();

	if ( myInput->keyPress( DIK_ESCAPE))
		PostQuitMessage(0);
}

void HUD::Render()
{
	//Show current score
	sprintf_s(hudPrint, "Score: %d", (int)score);
	font->DrawTextA(0, hudPrint, -1, &scoreRect, 
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_ARGB(255, 0, 51, 255));

	//Show current high score
	sprintf_s(hudPrint, "High Score: %d", (int)highScore);
	font->DrawTextA(0, hudPrint, -1, &highScoreRect, 
		DT_TOP | DT_CENTER | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 51, 255));

	//Show the current level
	sprintf_s(hudPrint, "L-%d", (int)level);
	font->DrawTextA(0, hudPrint, -1, &levelRect, 
		DT_BOTTOM | DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 51, 255));

	//display elapsed time
	sprintf_s(hudPrint, "Elapsed Time\n%d", (int)timer->GetMinutes());
	strcat(hudPrint, ":");
	if(timer->GetSeconds() <= 9)
	{
		strcat(hudPrint, "0");
	}
	sprintf_s(seconds, "%d", (int)timer->GetSeconds());
	strcat(hudPrint, seconds);

	//print time
	(hudPrint, (int)timer->GetMinutes());
	font->DrawTextA(0, hudPrint, -1, &timeRect, 
		DT_TOP | DT_RIGHT | DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 51, 255));

}

void HUD::Shutdown()
{
	delete timer;
}