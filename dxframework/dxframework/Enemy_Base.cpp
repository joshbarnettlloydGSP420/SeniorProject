#include "Enemy_Base.h"


Enemy_Base::Enemy_Base(void)
{
	// defalut values
	textureName = L"RedGhostTexture.JPEG";
	textureNumber = RedGhost;
	meshName = L"Dwarf.X";
	isDead = false;
	health = 100;
	attackPower = 50;
	defencePower = 50;
	attackRange = D3DXVECTOR4( 50, 50, 50, 0);
	wanderRange = D3DXVECTOR4( 50, 50, 50, 0);

	velUD = 0.0f;
	velLR = 0.0f;

	//scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//rotation = D3DXVECTOR3(0.0f, 0.15f, 0.0f);
}

Enemy_Base::Enemy_Base( short health, short attackPower, short defencePower, D3DXVECTOR4 position)
{
	this->health = health;
	this->attackPower = attackPower;
	this->defencePower = defencePower;
	this->textureName = textureName;

	//scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//rotation = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	velUD = 0.0f;
	velLR = 0.0f;
}


Enemy_Base::~Enemy_Base(void)
{
}

// Initialize all the variables for the enemies
void Enemy_Base::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* renderObject)
{
	device = m_pD3DDevice;
	render = renderObject;

	//scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	//rotation  = D3DXVECTOR3(0.0f, 0.55f, 0.0f);

	velUD = 5.0f;
	velLR = 5.0f;

	textureName = L"RedGhostTexture.JPG";
	textureNumber = RedGhost;
	meshName = L"RedGhost.X";
	isDead = false;
	health = 100;
	attackPower = 50;
	defencePower = 50;
	attackRange = D3DXVECTOR4( 50, 50, 50, 0);
	wanderRange = D3DXVECTOR4( 50, 50, 50, 0);

	// Set the Initial position of the enemy if none is specified.
	movement = new Enemy_Movement();
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->SetOrientation( 0.0f);
	movement->SetRotation( 0.0f);
	movement->SetLinear( D3DXVECTOR4(0, 0, 0, 0));
	movement->SetAngular( 0.0f);

	// Initial state of the enemy
	State = Wander;

	// Create the texture
	render->LoadTexture( textureName, textureNumber);

	// create 3D mesh from .x file
	render->LoadMesh( meshName, &objectMesh);
}

// Update the enemy
void Enemy_Base::Update( float dt, D3DXVECTOR4 playerPosition )
{ 
	playerPos = playerPosition;

	if ( health <= 0)
	{
		isDead = true;
	}

	wander.GetSteering( movement );
	//wander.GetKinematicSteering( movement);
	//UpdateState( State, dt );
	movement->GetNewOrientation();
	movement->Update(dt);
	//HavokMovement();
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
			//if (playerPos - movement->GetPosition() < wanderRange )
				//ChangeState( Seek );
			break;
		}
		// Seek out the player
	case Seek:
		{
			seek.GetSteering( movement, playerPos);
			// if in range of player then attack
			//if (playerPos - movement->GetPosition() < attackRange )
				//ChangeState( Attack );

			// if player is out of range then wander
			//else if (playerPos - movement->GetPosition() >= wanderRange )
				//ChangeState( Wander );
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

void Enemy_Base::Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat)
{
	//enemyGun->mPSys->draw(hwnd);

	// has to send in orientation to turn properly
	render->SetRotation( movement->GetOrientation());
	render->Render3DObject( movement->GetPosition(), objectMesh, veiwMat, projMat);
}


void Enemy_Base::CreateBodyObject(hkpWorld* world)
{
	//// Create a ridid body that can move dynamically about the scene.
	//hkpCharacterRigidBodyCinfo	bodyInfo;

	//// Capsule Parameters
	//hkVector4	vertexA(scale.x, movement->GetPosition().y + (scale.y / 2), scale.z, 0);	// Top
	//hkVector4	vertexB(scale.x, movement->GetPosition().y - (scale.y / 2), scale.z, 0);	// Bottom
	//hkReal		radius	=	(scale.x + scale.z) / 2;						// Radius

	//// Create Capsule Based on Parameters
	//hkpCapsuleShape* capsuleShape = new hkpCapsuleShape(vertexA, vertexB, radius);

	//// Set The Object's Properties
	//bodyInfo.m_shape = capsuleShape;
	//bodyInfo.m_position.set(movement->GetPosition().x, movement->GetPosition().y, movement->GetPosition().z, 0.0f);
	//bodyInfo.m_mass = 5.0f;

	//// Calculate Mass Properties
	//hkMassProperties massProperties;

	//hkpInertiaTensorComputer::computeShapeVolumeMassProperties(bodyInfo.m_shape, bodyInfo.m_mass, massProperties);
	//
	//// Create Rigid Body
	//rigidBody = new hkpCharacterRigidBody(bodyInfo);

	//// Add Rigid Body to the World
	//world->addEntity(rigidBody->getRigidBody());

	//// No longer need the reference on the shape, as the rigidbody owns it now
	//capsuleShape->removeReference();
}

void Enemy_Base::HavokMovement()
{
	hkpCharacterOutput output;

	if(movement->GetPosition().x < rigidBody->getPosition().getComponent(0))
	input.m_inputLR += velLR;
	else if(movement->GetPosition().x > rigidBody->getPosition().getComponent(0))
	input.m_inputLR -= velLR;

	if(movement->GetPosition().z < rigidBody->getPosition().getComponent(2))
	input.m_inputUD += velUD;
	else if(movement->GetPosition().z > rigidBody->getPosition().getComponent(2))
	input.m_inputUD -= velUD;
	
	input.m_up = hkVector4(0, 1, 0);
	input.m_forward.set(0, 0, 1);
	
	hkStepInfo stepInfo;
	stepInfo.m_deltaTime = 1.0f / 60.0f;
	stepInfo.m_invDeltaTime = 1.0f / (1.0f / 60.0f);

	input.m_stepInfo = stepInfo;
	input.m_characterGravity.set(0, -16, 0);
	input.m_velocity = rigidBody->getRigidBody()->getLinearVelocity();
	input.m_position = rigidBody->getRigidBody()->getPosition();

	rigidBody->checkSupport(stepInfo, input.m_surfaceInfo);

	context->update(input, output);

	rigidBody->setLinearVelocity(output.m_velocity, 1.0f / 60.0f);
}