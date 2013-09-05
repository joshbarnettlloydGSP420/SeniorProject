#include "HUD.h"


HUD::HUD(void)
{
	//player hud variables
	maxHealth = 100;
	currentHealth = 100;
	
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

	//rects to reference position
	SetRect(&scoreRect, 0, 0, 800, 600);
	SetRect(&highScoreRect, 0, 0, 800, 600);
	SetRect(&timeRect, 0, 0, 800, 600);
	SetRect(&livesRect, 0, 0, 800, 600);
	SetRect(&levelRect, 0, 0, 800, 600);

	//hud
	SetRect(&hudSheetRect, 218, 192, 505, 280);
	hudPosition.position = hudLocation;
	
	//health
	SetRect(&healthSheetRect, 32, 2, 242, 29);
	healthPosition.position.x = hudLocation.x + 37;
	healthPosition.position.y = hudLocation.y + 12;
	healthPosition.position.z = 0.0f;

	//shield
	SetRect(&shieldSheetRect, 32, 2, 242, 29);
	shieldPosition.position.x = hudLocation.x + 37;
	shieldPosition.position.y = hudLocation.y + 40;
	shieldPosition.position.z = 0.0f;
	
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
	//D3DXCreateTextureFromFile(device, "healthHUD.png", &hudTexture);
	hudOn = true;

}

void HUD::Update(float dt)
{
}

void HUD::Render(IDirect3DDevice9* device, ID3DXSprite* sprite)
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
	sprite->Draw(healthTexture, &healthSheetRect, &D3DXVECTOR3(0,0,0), &healthPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
	sprite->Draw(shieldTexture, &shieldSheetRect, &D3DXVECTOR3(0,0,0), &shieldPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));	
	sprite->Draw(hudTexture, &hudSheetRect, &D3DXVECTOR3(0,0,0), &hudPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
		
	}
}

void HUD::Shutdown()
{
	SAFE_RELEASE(hudTexture)
	SAFE_RELEASE(healthTexture)
	SAFE_RELEASE(shieldTexture)
}