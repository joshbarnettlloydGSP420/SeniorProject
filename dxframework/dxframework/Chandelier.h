#pragma once

#include "Object_Base.h"
#include "EntityManager.h"
#include "PSystem.h"
#include "RenderObject.h"
#include "SoundEffect.h"
#include "SoundLoader.h"
#include "AudioManager.h"

using namespace std;

class Chandelier
{
private:
	bool Shattered;

	SoundEffect* Shatter;

	// particle variables

	RenderObject*		render;

public:
	Object_Base* ChandelierObject;

	Chandelier(void);
	~Chandelier(void);

	void Init( Object_Player* Player, RenderObject* render , hkpWorld* world );

	void Update(float deltaTime, D3DXVECTOR3 eyePos, D3DXVECTOR3 lookAt);

	void Render(HWND hWnd, D3DXVECTOR3 eyePos,D3DXMATRIX viewMat, D3DXMATRIX projMat);

	void BulletCollision( float dt, Object_Player* player, gunType bulletColor);

	bool getShattered() { return Shattered; };
};

