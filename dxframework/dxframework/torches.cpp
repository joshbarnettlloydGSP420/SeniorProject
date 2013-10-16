#include "torches.h"
#include "Fire.h"

FourTorchPuzzle::FourTorchPuzzle()
{

	D3DXMatrixIdentity(&psysFireWorld);

	psysFireBox.maxPt = D3DXVECTOR3(INFINITY, INFINITY, INFINITY);
	psysFireBox.minPt = D3DXVECTOR3(-INFINITY, -INFINITY, -INFINITY);


	fireSystem1 = new FireRing(L"sprinkler.fx", "SprinklerTech", L"torch.dds", D3DXVECTOR3(0.0f, 0.0f, 0.0f), psysFireBox, 35, 0.0025f);
	fireSystem2 = new FireRing(L"sprinkler.fx", "SprinklerTech", L"torch.dds", D3DXVECTOR3(0.0f, 0.0f, 0.0f), psysFireBox, 35, 0.0025f);
	fireSystem3 = new FireRing(L"sprinkler.fx", "SprinklerTech", L"torch.dds", D3DXVECTOR3(0.0f, 0.0f, 0.0f), psysFireBox, 35, 0.0025f);
	fireSystem4 = new FireRing(L"sprinkler.fx", "SprinklerTech", L"torch.dds", D3DXVECTOR3(0.0f, 0.0f, 0.0f), psysFireBox, 35, 0.0025f);

	fireSystem1->SetType(1);
	fireSystem2->SetType(1);
	fireSystem3->SetType(1);
	fireSystem4->SetType(1);
}


FourTorchPuzzle::~FourTorchPuzzle()
{

}

void FourTorchPuzzle::Init( Object_Player* Player, RenderObject* renderer, hkpWorld* world )
{
	Torchlit = new SoundEffect();
	Torchlit = SoundLoader::GetInstance()->Load(false, false, "OOT_Fire_Ignite.wav");

	render = renderer;

	fireSystem1 = Player->fireSystem1;
	fireSystem2 = Player->fireSystem2;
	fireSystem3 = Player->fireSystem3;
	fireSystem4 = Player->fireSystem4;

	// Torch
	for(short i = 0; i < ARRAYSIZE(Torches); ++i)
	{
		Torches[i] = new Object_Base();
		Torches[i]->shape = BOX;
		Torches[i]->weight = UNMOVABLE;
		Torches[i]->scale = D3DXVECTOR3(0.8f, 1.5f, 1.5f);
	}

	// torch positions
	Torches[0]->position = D3DXVECTOR4(20.6f, 6.0f, -17.6f, 0.0f); // northeast corner
	Torches[1]->position = D3DXVECTOR4(20.6f, 6.0f, -32.4f, 0.0f); // southeast corner // 23.7
	Torches[2]->position = D3DXVECTOR4(-18.2f, 6.0f, -17.6f, 0.0f); // northwest corner // -16
	Torches[3]->position = D3DXVECTOR4(-18.2f, 6.0f, -32.4f, 0.0f); // southwest corner

	/*Puzzle_FT->fireSystem1->	*/

	Torches[0]->rotation = D3DXVECTOR3(1.6f,0.0f,0.0f); // NE
	Torches[1]->rotation = D3DXVECTOR3(1.6f,0.0f,0.0f); // SE
	Torches[2]->rotation = D3DXVECTOR3(-1.62f,0.0f,0.0f); // NW
	Torches[3]->rotation = D3DXVECTOR3(-1.62f,0.0f,0.0f); // SW

	render->LoadTexture( L"Metal_Texture.jpg", 10);

	for(short i = 0; i < ARRAYSIZE(Torches); ++i)
		render->LoadMesh(L"Torch.X", &Torches[i]->objectMesh);

	for(short i = 0; i < ARRAYSIZE(Torches); ++i)
		Torches[i]->createHavokObject(world);

	for(short i = 0; i < ARRAYSIZE(Torches); ++i)
		Torches[i]->scale = D3DXVECTOR3(5.1050f, 5.1050f, 5.1050f);

	for(short i = 0; i < ARRAYSIZE(Torches); ++i)
		TorchLit[i] = false;

	allTorchesLit = false;


}

void FourTorchPuzzle::Update(float deltaTime, D3DXVECTOR3 eyePos, D3DXVECTOR3 lookAt)
{
	TorchLit[0] == true;
			
	fireSystem1->setPosition(Torches[0]->getPosition());
	fireSystem1->update(deltaTime, eyePos, lookAt);		
	

	//if ( TorchLit[0] == true )
	//{		
	//	fireSystem1->setPosition(Torches[0]->getPosition());
	//	fireSystem1->update(deltaTime, eyePos, lookAt);		
	//}
	if ( TorchLit[1] == true )
	{		
		fireSystem2->setPosition(Torches[1]->getPosition());
		fireSystem2->update(deltaTime, eyePos, lookAt);		
	}

	if ( TorchLit[2] == true )
	{
		fireSystem3->setPosition(Torches[2]->getPosition());
		fireSystem3->update(deltaTime, eyePos, lookAt);
	}

	if ( TorchLit[3] == true )
	{
		fireSystem4->setPosition(Torches[3]->getPosition());
		fireSystem4->update(deltaTime, eyePos, lookAt);
	}

	if ( TorchLit[0] == true && TorchLit[1] == true&& TorchLit[2] == true&& TorchLit[3] == true)
		allTorchesLit = true;
}

void FourTorchPuzzle::Render(HWND hWnd, D3DXVECTOR3 eyePos, D3DXMATRIX viewMat,D3DXMATRIX projMat)
{
	//if ( TorchLit[0] == true )
	TorchLit[0] == true;
	fireSystem1->draw(hWnd, eyePos, viewMat * projMat);
	if ( TorchLit[1] == true )
	fireSystem2->draw(hWnd, eyePos, viewMat * projMat);
	if ( TorchLit[2] == true )
	fireSystem3->draw(hWnd, eyePos, viewMat * projMat);
	if ( TorchLit[3] == true )
	fireSystem4->draw(hWnd, eyePos, viewMat * projMat);

	//for(short i = 0; i < ARRAYSIZE(Torches); ++i)
		//render->Render_Object( Torches[i], D3DXVECTOR3(1.0f, -3.0f, 0.3f), viewMat, projMat);
	render->Render_Object( Torches[0], D3DXVECTOR3(-0.1f, -3.0f, 0.3f), viewMat, projMat);
	render->Render_Object( Torches[1], D3DXVECTOR3(-0.1f, -3.0f, 0.3f), viewMat, projMat);
	render->Render_Object( Torches[2], D3DXVECTOR3(-1.0f, -3.0f, 0.3f), viewMat, projMat);
	render->Render_Object( Torches[3], D3DXVECTOR3(-1.0f, -3.0f, 0.3f), viewMat, projMat);

}

// TODO: add collision stuff
void FourTorchPuzzle::BulletCollision( float dt, Object_Player* player, gunType bulletColor)
{
	hkAabb aabbBase;
	hkAabb aabbOut;

	// Object Hit Bullets
	if ( bulletColor == red )
	{
		for(short i = 0; i < ARRAYSIZE(Torches); ++i)
		{
			Torches[i]->rigidBody->getCollidable()->getShape()->getAabb(Torches[i]->rigidBody->getTransform(), 0.4f, aabbOut);
			player->bull[i].bulletObject->getCollidable()->getShape()->getAabb(player->bull[i].bulletObject->getTransform(), 0.4f, aabbBase);

			if(aabbBase.overlaps(aabbOut))
			{
				// when hit set to true
				TorchLit[i] = true;
				AudioManager::GetInstance()->PlaySFX(*Torchlit);
			}
		}
	}
}