#include "MenuMain.h"

MenuMain::MenuMain()
{
	menuState = m_MAIN_MENU;
}

MenuMain::~MenuMain()
{

}

void MenuMain::Update()
{
	BaseMenu::Update();

	if ( myInput->keyPress( DIK_RETURN))
	{
		if ( menuItemSelected == 1)
		{
			menuState = m_GAME;
		}
		else if ( menuItemSelected == 2)
		{
			menuState = m_OPTIONS_MENU;
		}
		else if ( menuItemSelected == 3)
		{
			menuState = m_QUIT;
		}
	}
}

void MenuMain::Render()
{
	// Call the base menu's render method to initialize some variables
	BaseMenu::Render();

	//m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Print Main Menu at the top of the screen
	sprintf(menuPrint,"MAIN MENU");
	SetRect(&m_rect,120,10,600,500);  
	option = D3DCOLOR_ARGB(255,150,0,240);

	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Game Start");
	SetRect(&m_rect,120,210,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Options Menu");
	SetRect(&m_rect,120,410,600,500);
	if(menuItemSelected == 2)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Quit");
	SetRect(&m_rect,120,550,600,500);
	if(menuItemSelected == 3)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	//m_pD3DSprite->End();
}