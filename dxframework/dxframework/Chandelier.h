#pragma once

#include "PuzzleManager.h"

class Chandelier
{
private:

	bool Broken;

public:
	Chandelier(void);
	~Chandelier(void);

	void Initialize(void);

	void Update(void);

	void Render(void);
};

