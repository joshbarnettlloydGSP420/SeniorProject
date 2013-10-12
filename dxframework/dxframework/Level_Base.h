#pragma once

#include "Enemy_RedGhost.h"
#include "Enemy_GreenGhost.h"
#include "Enemy_PurpleGhost.h"
#include "Enemy_YellowGhost.h"
#include "Enemy_Base.h"
#include "RenderObject.h"
#include "Room.h"

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

class Level_Base
{
protected:

	// List of enemies to be used
	std::vector<Enemy_Base*>		enemies; 

	// level constraints
	float x1;
	float x2;
	float z1;
	float z2;

	// Create the rooms
	Room*		Foyer;
	Room*		Ballroom;
	Room*		Diningroom;
	Room*		Kitchen;
	Room*		House;		// create

	// Current Room Player is in
	AREA		currentRoom;

	// check to see if the level has been completed of puzzles and enemies
	bool		levelCleared;

	// room variables
	bool		puzzleSolved;	
	bool		enemiesDead;

	
public:
	Level_Base(void);
	~Level_Base(void);

	virtual void Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender);
	virtual void InitRooms();
	virtual void Update( float dt, Object_Player* player, gunType bulletColor);
	virtual void Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat);

	bool LeveledClear(){ return levelCleared; };

	float RandomBinomial( float min, float max);

};
