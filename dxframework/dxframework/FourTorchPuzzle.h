#pragma once

#include "PuzzleManager.h"


class FourTorchPuzzle
{
private:
	// torch variables
	int TorchNumber;
	int TorchesLit;
	bool TorchLit;
	
public:
	FourTorchPuzzle();
	~FourTorchPuzzle();

	void Initialize(void);

	void Update(void);

	void Render(void);


};

