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


void FourTorchPuzzle::Update(int deltaTime, D3DXVECTOR3 eyePos, D3DXVECTOR3 lookAt)
{
	// code for collision checking

	//if( red bullet collides with torch)
	//{ TorchesLit +=1;
	// TorchLit = true; }

	// also need to change unlit torch to lit
	fireSystem1->update(deltaTime, eyePos, lookAt);
	fireSystem2->update(deltaTime, eyePos, lookAt);
	fireSystem3->update(deltaTime, eyePos, lookAt);
	fireSystem4->update(deltaTime, eyePos, lookAt);

}

void FourTorchPuzzle::Render(HWND hWnd, D3DXVECTOR3 eyePos, D3DXMATRIX viewMat,D3DXMATRIX projMat)
{

	fireSystem1->draw(hWnd, eyePos, viewMat * projMat);
	fireSystem2->draw(hWnd, eyePos, viewMat * projMat);
	fireSystem3->draw(hWnd, eyePos, viewMat * projMat);
	fireSystem4->draw(hWnd, eyePos, viewMat * projMat);

}
