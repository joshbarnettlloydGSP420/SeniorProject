#include "Enemy_GreenGhost.h"


Enemy_GreenGhost::Enemy_GreenGhost(void)
{
}


Enemy_GreenGhost::~Enemy_GreenGhost(void)
{
}

void Enemy_GreenGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);



	// initialize the variables
	isDead = false;
	health = 200;
	attackSpeed = 10;
	attackRange = 50;
	wanderRange = 100;

	// Set the Initial movement variables
	movement = new Enemy_Movement();
	movement->setPosition( D3DXVECTOR4(0, 1.0, 45.5, 0));
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->SetOrientation( 0.0f);
	movement->SetRotation( 0.0f);
	movement->SetLinear( D3DXVECTOR4(0, 0, 0, 0));
	movement->SetAngular( 0.0f);

	// set the initial state of the enemy
	State = Wander;
	miniGhostInitialized = false;
	attackInitialized = false;

	// Initialize the 3D model of the enemy.
	textureName = L"GreenGhostTexture.jpg";
	textureNumber = GreenGhost;
	meshName = L"GreenGhost.x";

	// Create the texture
	render->LoadTexture( textureName, textureNumber);

	// create 3D mesh from .x file
	render->LoadMesh( meshName, &objectMesh);

	miniGhostInitialized = false;
}

// if the enemy is hit with a bullet
void Enemy_GreenGhost::BulletCollision( LPCSTR bulletColor )
{
	// if the bullet is the same color as the ghost then lose health
	if ( bulletColor == "Green" )
		health -= 20;
	// else if the bullet is the opposite color then gain health and create mini ghosts
	else if ( bulletColor == "Red" )
	{
		health += 10;
		//ChangeState( Defence );
	}
	// else if other colors then gain more health and increase attackSpeed
	else
	{
		health += 20;
		
		if ( attackSpeed <= 40 )
			attackSpeed += 5;
		else
			attackSpeed = 40;
	}

	// if health is greater than 200 set it to a max of 200
	if ( health > 200 )
		health = 200;
}