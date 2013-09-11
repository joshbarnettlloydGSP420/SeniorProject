#include "Enemy_Base.h"


Enemy_Base::Enemy_Base(void)
{
	// defalut values
	textureName = "RedGhostTexture.JPEG";
	textureNumber = RedGhost;
	meshName = "Dwarf.X";
	isDead = false;
	health = 100;
	attackPower = 50;
	defencePower = 50;
	attackRange = D3DXVECTOR4( 50, 50, 50, 0);
	wanderRange = D3DXVECTOR4( 50, 50, 50, 0);
}


Enemy_Base::~Enemy_Base(void)
{
	//delete movement;
	//delete havokShape;
}

// Initialize all the variables for the enemies
void Enemy_Base::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* renderObject)
{
	device = m_pD3DDevice;
	render = renderObject;

	textureName = "RedGhostTexture.jpg";
	textureNumber = RedGhost;
	meshName = "RedGhost.X";
	isDead = false;
	health = 100;
	attackPower = 50;
	defencePower = 50;
	attackRange = D3DXVECTOR4( 50, 50, 50, 0);
	wanderRange = D3DXVECTOR4( 50, 50, 50, 0);

	// Set the Initial position of the enemy if none is specified.
	movement = new Enemy_Movement();
	movement->setPosition( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->SetOrientation( 0.0f);
	movement->SetRotation( 0.0f);
	movement->SetLinear( D3DXVECTOR4(0, 0, 0, 0));

	// Initial state of the enemy
	State = Attack;

	havokShape = new Object_Player();
	havokShape->position = movement->GetPosition();
	havokShape->shape = 3;	// CAPSULE SHAPE

	// Create the texture
	render->LoadTexture( textureName, textureNumber);

	// create 3D mesh from .x file
	render->LoadMesh( meshName, &havokShape->objectMesh);
}

// Update the enemy
void Enemy_Base::Update( float dt, D3DXVECTOR4 playerPosition )
{
	playerPos = playerPosition;

	if ( health <= 0)
	{
		isDead = true;
	}

	UpdateState( State, dt );
	movement->GetNewOrientation();
	movement->Update(dt);

	havokShape->position = movement->GetPosition();
	//havokShape->Update(dt);
}

// Change the state of the enemy based on current actions in the game
void Enemy_Base::UpdateState(StateType CurrentState, float dt)
{
	switch( CurrentState )
	{
		// Wander around the room
	case Wander:
		{
			wander.GetSteering( movement);
			// if player is in range then seek
			if (playerPos - movement->GetPosition() < wanderRange )
				ChangeState( Seek );
			break;
		}
		// Seek out the player
	case Seek:
		{
			seek.GetSteering( movement, playerPos );
			// if in range of player then attack
			if (playerPos - movement->GetPosition() < attackRange )
				ChangeState( Attack );

			// if player is out of range then wander
			else if (playerPos - movement->GetPosition() >= wanderRange )
				ChangeState( Wander );
			break;
		}
		// Run away from the player
	case Flee:
		{
			flee.GetSteering( movement, playerPos );
			// if out of range of player then wander
			if (playerPos - movement->GetPosition() >= wanderRange )
				ChangeState( Wander );
			break;
		}
		// Attack the player
	case Attack:
		{
			// initialize the attack
			attack.Init();

			// update the attack to fire at the player
			if (playerPos - movement->GetPosition() < attackRange )			
			attack.Update( dt, movement->GetPosition(), playerPos);
			// if health is low then flee
			if ( health < 40 )
			{
				ChangeState( Flee );
			}
			// TODO: if player attacks then guard 50% of the time
			// ChangeState ( Guard );
			break;
		}
		// Guard against player's attack
	case Guard:
		{
			// if health is low then flee
			if ( health < 40 )
			{
				ChangeState( Flee );
			}
			// TODO: if player is not attacking then attack
			// ChangeState ( Attack );
			break;
		}
	};
}

void Enemy_Base::Render(HWND hwnd, D3DXMATRIX viewMat, D3DXMATRIX projMat)
{
	attack.Render(hwnd);

	//havokShape->mPSys->draw(hwnd);

	render->Render3DObject( movement->GetPosition(), havokShape->objectMesh, viewMat, projMat);
}

void Enemy_Base::CreateHavokObject(hkpWorld* world)
{
	havokShape->createHavokObject( world );
}