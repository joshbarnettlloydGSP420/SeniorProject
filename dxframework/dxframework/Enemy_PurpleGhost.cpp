#include "Enemy_PurpleGhost.h"


Enemy_PurpleGhost::Enemy_PurpleGhost(void)
{
}


Enemy_PurpleGhost::~Enemy_PurpleGhost(void)
{
}

void Enemy_PurpleGhost::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	// call the enemy base init
	Enemy_Base::Init(m_pD3DDevice, m_pRender);

	// Set the Initial movement variables
	movement = new Enemy_Movement();
	movement->setPosition( D3DXVECTOR4(50, 1.0, 24.4, 0));
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->SetOrientation( 0.0f);
	movement->SetRotation( 0.0f);
	movement->SetLinear( D3DXVECTOR4(0, 0, 0, 0));
	movement->SetAngular( 0.0f);

	// set the initial state of the enemy
	State = Wander;
	attackInitialized = false;

	// Initialize the 3D model of the enemy.
	textureName = L"PurpleGhostTexture.jpg";
	textureNumber = PurpleGhost;
	meshName = L"RedGhost.x";

	// Create the texture
	render->LoadTexture( textureName, textureNumber);

	// create 3D mesh from .x file
	render->LoadMesh( meshName, &objectMesh);
}

// if the enemy is hit with a bullet
void Enemy_PurpleGhost::BulletCollision( float dt, Object_Player* player, gunType bulletColor)
{
	// collision variables
	hkAabb aabbBase;
	hkAabb aabbOut;

	if ( bulletCounter <= 0.0)
	{
		// Enemy Hits Bullets
		for(short i = 0; i < ARRAYSIZE(player->bull); ++i)
		{
			// get the aabb bounding box of the ghost
			rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.4f, aabbOut);
			// get the aabb bounding box of the player
			player->bull[i].bulletObject->getCollidable()->getShape()->getAabb(player->bull[i].bulletObject->getTransform(), 0.4f, aabbBase);

			// if the bullet has collision with the enemy then take appropriate action.
			if(aabbBase.overlaps(aabbOut))
			{
				// if the bullet is the opposite color as the ghost then lose health
				if ( bulletColor == yellow )
				{
					health -= 10;
					bulletCounter = 5.0 * dt;
				}
				// else if the bullet is the same color then gain health
				else if ( bulletColor == purple )
				{
					health += 20;
					bulletCounter = 5.0 * dt;
				}
				// else if other colors then gain health
				else
				{
					health += 10;
					bulletCounter = 5.0 * dt;
				}

				// if health is greater than 200 set it to a max of 200
				if ( health > 200 )
					health = 200;
			}

		}

	}
	else
		bulletCounter -= (1 * dt);
}