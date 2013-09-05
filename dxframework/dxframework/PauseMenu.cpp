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

<<<<<<< HEAD
	if ( myInput->keyDown( DIK_RETURN))
=======
	if ( myInput->keyPress( DIK_RETURN))
>>>>>>> origin/MartinezWorking
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
<<<<<<< HEAD
	if ( myInput->keyDown( DIK_P ))
=======
	if ( myInput->keyPress( DIK_P ))
>>>>>>> origin/MartinezWorking
	{
		pauseState = p_RESUME_GAME;
	}
}

void PauseMenu::Render()
{
	sprintf(menuPrint,"PAUSE MENU");
<<<<<<< HEAD
	SetRect(&m_rect,120,130,600,500);  
=======
	SetRect(&m_rect,120,30,600,500);  
>>>>>>> origin/MartinezWorking
	option = D3DCOLOR_ARGB(255,150,0,240);

	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Resume Game ");
<<<<<<< HEAD
	SetRect(&m_rect,120,330,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Restart Game");
	SetRect(&m_rect,120,530,600,500);
	if(menuItemSelected == 2)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Quit");
	SetRect(&m_rect,120,730,600,500);
	if(menuItemSelected == 3)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
=======
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
>>>>>>> origin/MartinezWorking
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);
}