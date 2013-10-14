#pragma once

#include "Object_Base.h"
#include "EntityManager.h"

class FourTorchPuzzle
{
private:
	// torch variables
	int TorchNumber;
	int TorchesLit;
	bool TorchLit;
	
public:
	Object_Base* Torches[4];

	FourTorchPuzzle();
	~FourTorchPuzzle();

	void Initialize(void);

	void Update(void);

	void Render(void);
};

