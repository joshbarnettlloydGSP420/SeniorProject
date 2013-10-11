#pragma once

#include "Enemy_RedGhost.h"
#include "Enemy_GreenGhost.h"
#include "Enemy_PurpleGhost.h"
#include "Enemy_YellowGhost.h"

#include <vector>
#include <random>

enum	AREA
{
	FOYER,
	BALLROOM,
	DININGROOM,
	KITCHEN,
	NO_ROOM
};

struct Room
{
	// Bounding Box Area for the Room
	hkAabb		boundingArea;

	// Room bools
	bool		puzzleSolved;	// Is that room's puzzle solved?
	bool		enemiesDead;	// Are all the enemies dead?
	bool		playerInRoom;	// Is the player currently in the room?

	// room position and scale for the bounding box
	D3DXVECTOR3	roomPos;
	D3DXVECTOR3	roomSize;

	D3DXVECTOR3 door1Pos;
	D3DXVECTOR3 door2Pos;

	// Enemies
	int			remainingEnemies;
};

class Level_Base
{
protected:
	// List of enemies to be used
	std::vector<Enemy_Base*>		enemies; 

	// level constraints
	float x1, x2, z1, z2;

	// Create the rooms
	Room		Foyer;
	Room		Ballroom;
	Room		Diningroom;
	Room		Kitchen;

	// Current Room Player is in
	AREA		currentRoom;
	
public:
	Level_Base(void);
	~Level_Base(void);

	virtual void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	virtual void InitRooms();
	virtual void Update( float dt, Object_Player* player, gunType bulletColor);
	virtual void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);

	float RandomBinomial( float min, float max);
};
