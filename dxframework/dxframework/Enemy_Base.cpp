#include "Enemy_Base.h"


Enemy_Base::Enemy_Base(void)
{
}


Enemy_Base::~Enemy_Base(void)
{
}

// Initialize all the variables for the enemies
void Enemy_Base::Init(IDirect3DDevice9* m_pD3DDevice)
{
	device = m_pD3DDevice;

	// Set the Initial position of the enemy if none is specified.
	movement = new Enemy_Movement();
	movement->setPosition( D3DXVECTOR4( 0, 0, 50, 0 ));
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->SetOrientation( 0.0f);
	movement->SetRotation( 0.0f);
	movement->SetLinear( D3DXVECTOR4(0, 0, 0, 0));

	// Initial state of the enemy
	State = Wander;
}

// Update the enemy
void Enemy_Base::Update( float dt )
{
	if ( health <= 0)
	{
		isDead = true;
	}

	UpdateState( State );
	movement->GetNewOrientation();
	movement->Update(dt);
}

// Change the state of the enemy based on current actions in the game
void Enemy_Base::UpdateState(StateType CurrentState)
{
	switch( CurrentState )
	{
	// Wander around the room
	case Wander:
		{
			//wander.GetSteering( movement);
			// TODO: if player is in range then seek
			// ChangeState( Seek );
			break;
		}
	// Seek out the player
	case Seek:
		{
			//seek.GetSteering( movement, D3DXVECTOR4( 0, 0, 100, 0) );
			// TODO: if in range of player then attack
			// ChangeState( Attack );
			// if player is out of range then wander
			// ChangeState( Wander );
			break;
		}
	// Run away from the player
	case Flee:
		{
			// flee.GetSteering( movement);
			// if out of range of player then wander
			// ChangeState( Wander );
			break;
		}
	// Attack the player
	case Attack:
		{
			// TODO: if health is low then flee
			// ChangeState( Flee );
			// if player attacks then guard
			// ChangeState ( Guard );
			break;
		}
	// Guard against player's attack
	case Guard:
		{
			// TODO: if health is low then flee
			// ChangeState( Flee );
			// if player is not attacking then attack
			// ChangeState ( Attack );
			break;
		}
	};
}

void Enemy_Base::Render()
{
	model->setPosition( movement->GetPosition());
	model->render( device );
}