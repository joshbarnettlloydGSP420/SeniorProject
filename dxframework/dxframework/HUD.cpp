#include "HUD.h"


HUD::HUD(void)
{
	//enum
	color = g;

	//player hud variables
	maxHealth = 100;
	currentHealth = 100;
	
	maxShield = 100;
	currentShield = 100;
	
	//
	//bullets = 20;

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
	
	// ammo
	SetRect(&ammoSheetRect, 265, 235, 432, 325);
	ammoPosition.position.x = 0;
	ammoPosition.position.y = 510;
	ammoPosition.position.z = 0.0f;

	//SetRect(&purpleAmmoSheetRect, 297, 217, 342, 262);
	//ammoBulletPosition.position.x = ammoPosition.position.x + 0;
	//ammoBulletPosition.position.y = ammoPosition.position.y + 25;
	//ammoBulletPosition.position.z = ammoPosition.position.z;
	//
	//SetRect(&greenAmmoSheetRect, 297, 217, 342, 262);
	//ammoBulletPosition2.position.x = ammoPosition.position.x + 0;
	//ammoBulletPosition2.position.y = ammoPosition.position.y + 25;
	//ammoBulletPosition2.position.z = ammoPosition.position.z;

	//SetRect(&blueAmmoSheetRect, 297, 217, 342, 262);
	//ammoBulletPosition3.position.x = ammoPosition.position.x + 0;
	//ammoBulletPosition3.position.y = ammoPosition.position.y + 25;
	//ammoBulletPosition3.position.z = ammoPosition.position.z;

	SetRect(&bulletSheetRect, 297, 217, 342, 262);
	bulletPosition.position = D3DXVECTOR3(ammoPosition.position.x, ammoPosition.position.y + 25, ammoPosition.position.z);

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
	
	D3DXCreateTextureFromFileExA(device, "ammoHUD.png", 800, 600, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &ammoTexture);
		
	D3DXCreateTextureFromFileExA(device, "purpleAmmoHUD.png", 640, 480, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &purpleAmmoTexture);

	D3DXCreateTextureFromFileExA(device, "greenAmmoHUD.png", 640, 480, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &greenAmmoTexture);

	D3DXCreateTextureFromFileExA(device, "blueAmmoHUD.png", 640, 480, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		0, 0, &blueAmmoTexture);


	//D3DXCreateTextureFromFile(device, "healthHUD.png", &hudTexture);
	hudOn = true;

}

void HUD::Update(float dt)
{
}

void HUD::Render(IDirect3DDevice9* device, ID3DXSprite* sprite, int colorSwitch)
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
	sprite->Draw(ammoTexture, &ammoSheetRect, &D3DXVECTOR3(0,0,0), &ammoPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
	switch(colorSwitch)
	{
	case 0:
		sprite->Draw(greenAmmoTexture, &bulletSheetRect, &D3DXVECTOR3(0,0,0), &bulletPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;	
	case 1:
		sprite->Draw(blueAmmoTexture, &bulletSheetRect, &D3DXVECTOR3(0,0,0), &bulletPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	case 2:
		sprite->Draw(purpleAmmoTexture, &bulletSheetRect, &D3DXVECTOR3(0,0,0), &bulletPosition.position, D3DCOLOR_ARGB(255, 255, 255, 255));
		break;
	}
	}
}

void HUD::setColor(colorSwitch color)
{
	this->color = color;
}

void HUD::Shutdown()
{
	SAFE_RELEASE(hudTexture)
	SAFE_RELEASE(healthTexture)
	SAFE_RELEASE(shieldTexture)
	SAFE_RELEASE(ammoTexture)
	SAFE_RELEASE(purpleAmmoTexture)
	SAFE_RELEASE(greenAmmoTexture)
}