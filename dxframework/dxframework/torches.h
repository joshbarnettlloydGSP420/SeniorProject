
#pragma once

#include "Object_Base.h"
#include "EntityManager.h"
#include "PSystem.h"


using namespace std;

class FourTorchPuzzle
{
private:
	// torch variables
	int TorchNumber;
	int TorchesLit;
	bool TorchLit;
	
	// particle variables


	AABB psysFireBox;
	D3DXMATRIX psysFireWorld;

public:

	Object_Base* Torches[4];
	PSystem*	fireSystem1;
	PSystem*	fireSystem2; 
	PSystem*	fireSystem3; 
	PSystem*	fireSystem4;

	FourTorchPuzzle();
	~FourTorchPuzzle();

	void Update(int deltaTime, D3DXVECTOR3 eyePos, D3DXVECTOR3 lookAt);

	void Render(HWND hWnd, D3DXVECTOR3 eyePos,D3DXMATRIX viewMat,D3DXMATRIX projMat);
};