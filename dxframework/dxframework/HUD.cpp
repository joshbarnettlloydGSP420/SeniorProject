#include "HUD.h"


HUD::HUD(void)
{
<<<<<<< HEAD
	//player hud variables
	maxHealth = 100.0f;
	currentHealth = 100.0f;
	
	maxShield = 100;
	currentShield = 100;
	
	//
	bullets = 50;

	score = 400;
	highScore = 400;

	level = 1;
	hudOn = true;


	//hud pos
	hudLocation = D3DXVECTOR3(0,0,0);
=======
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
>>>>>>> origin/HeatherWorking

	//rects to reference position
	SetRect(&scoreRect, 0, 0, 800, 600);
	SetRect(&highScoreRect, 0, 0, 800, 600);
	SetRect(&timeRect, 0, 0, 800, 600);
	SetRect(&livesRect, 0, 0, 800, 600);
	SetRect(&levelRect, 0, 0, 800, 600);

<<<<<<< HEAD
	//hud
	SetRect(&hudSheetRect, 218, 192, 505, 280);
	hudPosition.position = hudLocation;
	
	//health
	SetRect(&healthSheetRect, 32, 2, 242, 29);
	healthPosition.position.x = hudLocation.x + 37;
	healthPosition.position.y = hudLocation.y + 12;

	//shield
	SetRect(&shieldSheetRect, 32, 2, 242, 29);
	shieldPosition.position.x = hudLocation.x + 37;
	shieldPosition.position.y = hudLocation.y + 40;
	
	//black bar background stuff
	//behind health
	SetRect(&blackBar1SheetRect, 32, 2, 242, 29);
	blackBar1Position.position.x = hudLocation.x + 37;
	blackBar1Position.position.y = hudLocation.y + 12;

	//behind shield
	SetRect(&blackBar2SheetRect, 32, 2, 242, 29);
	blackBar2Position.position.x = hudLocation.x + 37;
	blackBar2Position.position.y = hudLocation.y + 40;

	//var for manip size of bars
	widthHealth = healthSheetRect.right;
	widthShield = shieldSheetRect.right;
}


HUD::~HUD(void)
{
}


void HUD::Init(IDirect3DDevice9* device)
{
	D3DXCreateTextureFromFileExA(device, "healthHUD.png", 800, 600, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &hudTexture);
	
	D3DXCreateTextureFromFileExA(device, "LifeBar.png", 256, 32, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &healthTexture);

	D3DXCreateTextureFromFileExA(device, "ShieldBar.png", 256, 32, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &shieldTexture);

	D3DXCreateTextureFromFileExA(device, "blackBar.png", 256, 32, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &blackBarTexture);
	//D3DXCreateTextureFromFile(device, "healthHUD.png", &hudTexture);

=======
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
>>>>>>> origin/HeatherWorking
}

void HUD::Update(float dt)
{
<<<<<<< HEAD
	//example of getting hit
	if(currentHealth >= 50)
		currentHealth -= .2f*(dt*.02);
}

void HUD::Render(IDirect3DDevice9* device, ID3DXFont* font, ID3DXSprite* sprite, D3DXIMAGE_INFO imageInfo)
{

	if(hudOn)
	{
		/**********************************************************************************************************/
		/**									EQUATIONS FOR REFLECTING SUBTRACTED HEALTH						***/
		/**********************************************************************************************************/
		
		//health
		float remainingHealth = widthHealth - (widthHealth * (  (maxHealth - currentHealth) / maxHealth));

		if(remainingHealth < 32)
			remainingHealth += 32;

		healthSheetRect.right = remainingHealth;

		//shield
		float remainingShield = widthShield - (widthShield * (  (maxShield - currentShield) / maxShield));

		if(remainingShield < 32)
			remainingShield += 32;

		shieldSheetRect.right = remainingShield;
		/**********************************************************************************************************/

	//SetRect(&scoreRect, 0, 0, 800, 600);
	//sprintf_s(hudPrint, "Score: %d", (int)score);
	//font->DrawTextA(0, hudPrint, -1, &scoreRect, 
	//	DT_LEFT | DT_TOP | DT_NOCLIP,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));
	//	
	sprite->Draw(blackBarTexture, &blackBar1SheetRect, &D3DXVECTOR3(0,0,0), &blackBar1Position.position, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->Draw(blackBarTexture, &blackBar2SheetRect, &D3DXVECTOR3(0,0,0), &blackBar2Position.position, D3DCOLOR_ARGB(255, 255, 255, 255));

	sprite->Draw(healthTexture, &healthSheetRect, &D3DXVECTOR3(0,0,0), &healthPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->Draw(shieldTexture, &shieldSheetRect, &D3DXVECTOR3(0,0,0), &shieldPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));	
	sprite->Draw(hudTexture, &hudSheetRect, &D3DXVECTOR3(0,0,0), &hudPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
		
	}
=======
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

>>>>>>> origin/HeatherWorking
}

void HUD::Shutdown()
{
<<<<<<< HEAD
	SAFE_RELEASE(hudTexture)
	SAFE_RELEASE(healthTexture)
	SAFE_RELEASE(shieldTexture)
=======
	delete timer;
>>>>>>> origin/HeatherWorking
}