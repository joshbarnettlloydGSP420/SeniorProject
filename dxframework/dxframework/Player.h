#pragma once
#include "Object_Base.h"

class Player
{
private:
	Object_Base*	objectBase;

public:
	Player(void);
	~Player(void);

	void Init (HavokCore* havok );
	void Update( float dt);
	void Render();
};

