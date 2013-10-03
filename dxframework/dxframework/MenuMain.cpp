#include "MenuMain.h"

MenuMain::MenuMain()
{
	menuState = m_MAIN_MENU;
}

MenuMain::~MenuMain()
{

}


bool MenuMain::Init(InputManager* input, IDirect3DDevice9*	m_pD3DDevice)
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

	D3DXCreateFont(m_pD3DDevice, 110, 0, FW_BOLD, 0, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("SanitariumBB"), 
		&m_pD3DFont2);

	// set the initial selected item
	menuItemSelected = 1;

	// if no image is chosen this will be the default for the background
	backgroundFileName = L"haunted_house.jpg";

	// Create the background texture
	D3DXCreateTextureFromFileEx(m_pD3DDevice, backgroundFileName ,0,0,0,0,D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &backgroundTexture);

	// set back ground position
	backGroundPos = D3DXVECTOR3(0,0,0);

	// Load bgm
	MenuMusic = new SoundEffect();
	MenuMusic = SoundLoader::GetInstance()->LoadBGM("MainMenuMusic.ogg");
	AudioManager::GetInstance()->PlayBGM(*MenuMusic);
	AudioManager::GetInstance()->SetBGMVolume(1.0f);

	// Load sound effects
	MenuBeep = new SoundEffect();
	MenuBeep = SoundLoader::GetInstance()->Load(false, false, "MenuBeep2.mp3");
	return true;
}

void MenuMain::Update()
{
	BaseMenu::Update();

	if (myInput->keyDown( DIK_RETURN))
	{
		if ( menuItemSelected == 1)
		{
			menuState = m_GAME;
			MenuMusic->Free();
			GameBGM = SoundLoader::GetInstance()->LoadBGM("DST-TheHauntedChaple.mp3");
			AudioManager::GetInstance()->PlayBGM(*GameBGM);
			AudioManager::GetInstance()->SetBGMVolume(5.0);

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

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
	DrawBackGround();
	// Print Main Menu at the top of the screen
	sprintf(menuPrint,"Ghost Hunter X");
	SetRect(&m_rect,170,-30,600,500);  
	option = D3DCOLOR_ARGB(255,0,0,240);

	
	m_pD3DFont2->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Game Start");
	SetRect(&m_rect,130,210,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Options Menu");
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

	//m_pD3DSprite->End();
}


void MenuMain::DrawBackGround()
{
	
	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	m_pD3DSprite->SetTransform(&identity);
	D3DXMATRIX texScaling;
	D3DXMatrixScaling(&texScaling, 1.0f, 1.0f, 0.0f);
	m_pD3DDevice->SetTransform(D3DTS_TEXTURE0, &texScaling);

	D3DXMATRIX T, S;
	D3DXMatrixTranslation(&T,  backGroundPos.x,  backGroundPos.y,  backGroundPos.z);
	D3DXMatrixScaling(&S, 1.0f, 1.2f, 0.0f);
	m_pD3DSprite->SetTransform(&(S*T));

	// Draw the background sprite.
	m_pD3DSprite->Draw(backgroundTexture, 0, 0, 0, D3DCOLOR_XRGB(255, 255, 255));
	m_pD3DSprite->Flush();
	D3DXMatrixScaling(&texScaling, 1.0f, 1.0f, 1.0f);
	m_pD3DDevice->SetTransform(D3DTS_TEXTURE0, &texScaling);
}