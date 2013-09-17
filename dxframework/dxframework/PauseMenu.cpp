#include "PauseMenu.h"


PauseMenu::PauseMenu(void)
{
	pauseState = p_PAUSE_MENU;
}


PauseMenu::~PauseMenu(void)
{
}

bool PauseMenu::Init(InputManager* input, IDirect3DDevice9*	m_pD3DDevice)
{
// Local pointer to the input manager
	myInput = input;
	this->m_pD3DDevice = m_pD3DDevice;

	// create the SPRITE object
	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);

	// create a FONT object
	AddFontResourceEx(L"SanitariumBB.otf", FR_PRIVATE, 0);
	D3DXCreateFont(m_pD3DDevice, 30, 0, FW_BOLD, 0, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("SanitariumBB"), 
		&m_pD3DFont);

	// set the initial selected item
	menuItemSelected = 1;

	// if no image is chosen this will be the default for the background
	backgroundFileName = L"pausemenu.jpg";
	
	// Create the background texture
	D3DXCreateTextureFromFileEx(m_pD3DDevice, backgroundFileName ,0,0,0,0,D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &backgroundTexture);

	// set back ground position
	backGroundPos = D3DXVECTOR3(0,0,0);

	// sound menu beep
	// Load sound effects
	MenuBeep = new SoundEffect();
	MenuBeep = SoundLoader::GetInstance()->Load(false,false ,"MenuBeep2.mp3");
	AudioManager::GetInstance()->SetSFXVolume(1.0f);
	return true;
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
	/*sprintf(menuPrint,"PAUSE MENU");
	SetRect(&m_rect,120,30,600,500);  
	option = D3DCOLOR_ARGB(255,150,0,240);*/

	DrawBackground();
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


void PauseMenu::DrawBackground()
{
	

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	m_pD3DSprite->SetTransform(&identity);
	D3DXMATRIX texScaling;
	D3DXMatrixScaling(&texScaling, 1.0f, 1.00f, 0.0f);
	m_pD3DDevice->SetTransform(D3DTS_TEXTURE0, &texScaling);

	D3DXMATRIX T, S;
	D3DXMatrixTranslation(&T,  backGroundPos.x, - backGroundPos.y, - backGroundPos.z);
	D3DXMatrixScaling(&S, 2.7f, 3.0f, 0.0f);
	m_pD3DSprite->SetTransform(&(S*T));

	// Draw the background sprite.
	m_pD3DSprite->Draw(backgroundTexture, 0, 0, 0, D3DCOLOR_XRGB(255, 255, 255));
	m_pD3DSprite->Flush();
	D3DXMatrixScaling(&texScaling, 1.0f, 1.0f, 1.0f);
	m_pD3DDevice->SetTransform(D3DTS_TEXTURE0, &texScaling);
}