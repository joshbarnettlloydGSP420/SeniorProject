#include "BaseMenu.h"



BaseMenu::BaseMenu(void)
{
}


BaseMenu::~BaseMenu(void)
{

}

bool BaseMenu::Init(InputManager* input, IDirect3DDevice9*	m_pD3DDevice)
{
	// Local pointer to the input manager
	myInput = input;
	this->m_pD3DDevice = m_pD3DDevice;

	// create the SPRITE object
	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);

	// create a FONT object
	AddFontResourceEx("SanitariumBB.otf", FR_PRIVATE, 0);
	D3DXCreateFont(m_pD3DDevice, 30, 0, FW_BOLD, 0, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("SanitariumBB"), 
		&m_pD3DFont);

	// set the initial selected item
	menuItemSelected = 1;

	// if no image is chosen this will be the default for the background
	backgroundFileName = "mainMenuBackground.png";

	// Create the background texture
	D3DXCreateTextureFromFileEx(m_pD3DDevice, backgroundFileName ,0,0,0,0,D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &backgroundTexture);

	// set back ground position
	backGroundPos = D3DXVECTOR3(0,0,0);
	return true;
}

void BaseMenu::Update()
{
	myInput->getInput();

	if (myInput->keyPress( DIK_UP))
	{
		menuItemSelected--;
	}
	else if ( myInput->keyPress( DIK_DOWN))
	{
		menuItemSelected++;
	}

	if ( menuItemSelected < 1)
		menuItemSelected = 3;
	if ( menuItemSelected > 3)
		menuItemSelected = 1;

	if (myInput->keyPress( DIK_ESCAPE))
	{
		PostQuitMessage(0);
	}
}

void BaseMenu::Render()
{
	
}

void BaseMenu::onLostDevice()
{
	m_pD3DFont->OnLostDevice();
	m_pD3DSprite->OnLostDevice();
}

void BaseMenu::onResetDevice()
{
	m_pD3DFont->OnResetDevice();
	m_pD3DSprite->OnResetDevice();
}

