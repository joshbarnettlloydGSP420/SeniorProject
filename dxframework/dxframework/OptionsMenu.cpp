#include "OptionsMenu.h"


OptionsMenu::OptionsMenu(void)
{
}


OptionsMenu::~OptionsMenu(void)
{
}

bool OptionsMenu::Init(InputManager* input, IDirect3DDevice9* m_pD3DDevice, HWND* wndHandle, D3DPRESENT_PARAMETERS* D3dpp)
{
	BaseMenu::Init( input, m_pD3DDevice );
	hwnd = wndHandle;
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
	backgroundFileName = "options menu.jpg";

	// Create the background texture
	D3DXCreateTextureFromFileEx(m_pD3DDevice, backgroundFileName ,0,0,0,0,D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &backgroundTexture);

	// set back ground position
	backGroundPos = D3DXVECTOR3(0,0,0);
	return true;
}

void OptionsMenu::Update()
{
	BaseMenu::Update();

	if ( menuItemSelected < 1)
		menuItemSelected = 2;

	if ( menuItemSelected > 2)
		menuItemSelected = 1;

	if ( myInput->keyDown(DIK_RETURN))
	{
			if ( menuItemSelected == 1)
			{
			optionsState = o_CREDITS;
			InitVideo(L"Temp.wmv");
			videoControl->Run();

			videoEvent->GetEvent(&evCode, &eventParam1, &eventParam2, 0);

			// wait for the video to finish, or wait until the user hits Enter/Return Key
			if(myInput->keyDown( DIK_SPACE) || (evCode == EC_COMPLETE) ) 
			{
				optionsState = o_OPTIONS_MENU;
				DestroyVideo();
			}
			}
		else if ( menuItemSelected == 2)
		{
			optionsState = o_QUIT_TO_MAIN;
		}
	}
}

void OptionsMenu::Render()
{
	// Call the base menu's render method to initialize some variables
	BaseMenu::Render();

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
	DrawBackground();
	// Print Main Menu at the top of the screen
	sprintf(menuPrint,"OPTIONS MENU");
	SetRect(&m_rect,120,130,600,500);  
	option = D3DCOLOR_ARGB(255,150,0,240);

	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	
	sprintf(menuPrint,"Credits");
	SetRect(&m_rect,120,330,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Exit to Main Menu");
	SetRect(&m_rect,120,530,600,500);
	if(menuItemSelected == 2)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	m_pD3DSprite->End();
}

void OptionsMenu::InitVideo(LPCWSTR vidName)
{
	CoInitialize(NULL); 

	CoCreateInstance( CLSID_FilterGraph, NULL,
		CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
		(void**)&videoGraph);

	videoGraph->QueryInterface(IID_IMediaControl,
		(void**)&videoControl);

	videoGraph->QueryInterface(IID_IMediaEvent,
		(void**)&videoEvent);

	// building a filter graph for our video
	videoGraph->RenderFile(vidName, NULL);

	//video window
	videoControl->QueryInterface(IID_IVideoWindow,
		(void**)&videoWindow);

	// setup the window
	videoWindow->put_Owner((OAHWND)hwnd);

	// Set the style
	videoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);

	// Obtain the size of the window
	RECT WinRect;
	GetClientRect(*hwnd, &WinRect);

	// Set the video size to the size of the window
	videoWindow->SetWindowPosition(WinRect.left, WinRect.top, 
		WinRect.right, WinRect.bottom);
}

void OptionsMenu::DestroyVideo()
{
	videoControl->Stop();
	videoWindow->put_Visible(OAFALSE);
	SAFE_RELEASE(videoControl);
	SAFE_RELEASE(videoWindow);
	SAFE_RELEASE(videoGraph);
}

void OptionsMenu::DrawBackground()
{
	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	m_pD3DSprite->SetTransform(&identity);
	D3DXMATRIX texScaling;
	D3DXMatrixScaling(&texScaling, 1.f, 1.00f, 0.0f);
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