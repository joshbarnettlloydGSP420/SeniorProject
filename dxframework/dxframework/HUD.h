#pragma once
#pragma comment(lib, "winmm.lib")
//////////////////////////////////////////////////////////////////////////
// Direct3D 9 headers and libraries required
//////////////////////////////////////////////////////////////////////////
<<<<<<< HEAD
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
=======
#include "InputManager.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "Timer.h"
>>>>>>> origin/HeatherWorking

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
<<<<<<< HEAD

// Macro to release COM objects fast and safely
#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}


class HUD
{
private:
	//player variables
	float widthHealth;
	float widthShield;

	// health and shield
	float maxHealth;
	float currentHealth;
	
	float maxShield;
	float currentShield;


	int bullets;

	int level;
	bool hudOn;

	char hudPrint[30];

	int score, highScore;

	// all rects
	RECT scoreRect, highScoreRect, timeRect, livesRect, levelRect, hudRect, healthRect, shieldRect, blackBar1Rect, blackBar2Rect;

	//exact cuts of the hud items
	RECT hudSheetRect;
	RECT healthSheetRect;
	RECT shieldSheetRect;
	RECT blackBar1SheetRect;
	RECT blackBar2SheetRect;


	//hud textures
	IDirect3DTexture9* hudTexture;
	IDirect3DTexture9* healthTexture;
	IDirect3DTexture9* shieldTexture;
	IDirect3DTexture9* blackBarTexture;

	struct rectPositions
	{
		D3DXVECTOR3 position;
	}
	hudPosition, healthPosition, shieldPosition, blackBar1Position, blackBar2Position;

	//hud position variables, the health/shield bars will be dependant on hud pos
	D3DXVECTOR3 hudLocation;
=======
class HUD
{
private:
	//pacman variables
	int score;
	int highScore;
	int lives;
	int level;
	bool hudOn;

	char seconds[30];
	char hudPrint[30];

	RECT scoreRect, highScoreRect, timeRect, livesRect, levelRect;
	
	//timer
	CTimer* timer;
	float currentTime;
	float previousTime;

	ID3DXFont*	font;			// Font Object
	InputManager* myInput;
>>>>>>> origin/HeatherWorking

public:
	HUD(void);
	~HUD(void);

<<<<<<< HEAD
	void Init(IDirect3DDevice9* device);

	void Update(float dt);

	void Render(IDirect3DDevice9* device, ID3DXFont* font, ID3DXSprite* sprite, D3DXIMAGE_INFO imageInfo);

	void Shutdown();

=======
	void Init(IDirect3DDevice9* m_pD3DDevice, InputManager* input);

	void Update(float dt);

	void Render();

	void Shutdown();
>>>>>>> origin/HeatherWorking
};

