#include "Chandelier.h"


Chandelier::Chandelier(void)
{
}


Chandelier::~Chandelier(void)
{
}

void Chandelier::Init( Object_Player* Player, RenderObject* renderer, hkpWorld* world )
{
	render = renderer;

	// Chandelier
	ChandelierObject = new Object_Base();
	ChandelierObject->shape = BOX;
	ChandelierObject->weight = UNMOVABLE;
	ChandelierObject->scale = D3DXVECTOR3(0.8f, 1.5f, 1.5f);

	// Chandelier position
	ChandelierObject->position = D3DXVECTOR4(10.6f, 6.0f, -17.6f, 0.0f);

	ChandelierObject->rotation = D3DXVECTOR3(1.6f,0.0f,0.0f);

	// Chandelier rendering
	render->LoadTexture( L"Metal_Texture.jpg", 10);

	render->LoadMesh(L"Chandalier.X", &ChandelierObject->objectMesh);

	ChandelierObject->createHavokObject(world);

	ChandelierObject->scale = D3DXVECTOR3(5.1050f, 5.1050f, 5.1050f);

	Shattered = false;

}

void Chandelier::Update(float deltaTime, D3DXVECTOR3 eyePos, D3DXVECTOR3 lookAt)
{

}

void Chandelier::Render(HWND hWnd, D3DXVECTOR3 eyePos, D3DXMATRIX viewMat,D3DXMATRIX projMat)
{
	render->Render_Object( ChandelierObject, D3DXVECTOR3(-0.1f, -3.0f, 0.3f), viewMat, projMat);
}

void Chandelier::BulletCollision( float dt, Object_Player* player, gunType bulletColor)
{

}