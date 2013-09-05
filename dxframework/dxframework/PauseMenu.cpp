#include "PauseMenu.h"


PauseMenu::PauseMenu(void)
{
	pauseState = p_PAUSE_MENU;
}


PauseMenu::~PauseMenu(void)
{
}

void PauseMenu::Update()
{
	BaseMenu::Update();

	if ( myInput->keyPress( DIK_RETURN))
	{
		if ( menuItemSelected == 1)
		{
			pauseState = p_RESUME_GAME;
		}
		else if ( menuItemSelected == 2)
		{
			pauseState = p_RESTART;
		}
		else if ( menuItemSelected == 3)
		{
			pauseState = p_MAIN_MENU;
		}
	}
	if ( myInput->keyPress( DIK_P ))
	{
		pauseState = p_RESUME_GAME;
	}
}

void PauseMenu::Render()
{
	sprintf(menuPrint,"PAUSE MENU");
	SetRect(&m_rect,120,30,600,500);  
	option = D3DCOLOR_ARGB(255,150,0,240);

	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Resume Game ");
	SetRect(&m_rect,120,220,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Restart Game");
	SetRect(&m_rect,120,410,600,500);
	if(menuItemSelected == 2)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Quit");
	SetRect(&m_rect,120,550,600,500);
	if(menuItemSelected == 3)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);
}