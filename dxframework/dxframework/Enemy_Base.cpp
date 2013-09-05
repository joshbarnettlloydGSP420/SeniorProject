#include "Enemy_Base.h"


Enemy_Base::Enemy_Base(void)
{
<<<<<<< HEAD
=======
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

	shape = 3;

	velUD = 0.0f;
	velLR = 0.0f;

	mass = 5.0f;

	position = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.15f, 0.0f);
}

Enemy_Base::Enemy_Base(short health, short attackPower, short defencePower, D3DXVECTOR4 position, LPCSTR textureName, int textureNumer)
{
	this->health = health;
	this->attackPower = attackPower;
	this->defencePower = defencePower;
	this->position = position;
	this->textureName = textureName;
	this->textureNumber = textureNumber;

	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	shape = 3;

	velUD = 0.0f;
	velLR = 0.0f;

	mass = 5.0f;
>>>>>>> origin/MartinezWorking
}


Enemy_Base::~Enemy_Base(void)
{
<<<<<<< HEAD
}

// Initialize all the variables for the enemies
void Enemy_Base::Init(IDirect3DDevice9* m_pD3DDevice)
{
	device = m_pD3DDevice;

	// Set the Initial position of the enemy if none is specified.
	movement = new Enemy_Movement();
	movement->setPosition( D3DXVECTOR4( 0, 0, 50, 0 ));
=======
	//delete movement;
	//delete havokShape;
}

// Initialize all the variables for the enemies
void Enemy_Base::Init(IDirect3DDevice9* m_pD3DDevice, RenderObject* renderObject)
{
	device = m_pD3DDevice;
	render = renderObject;

	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation  = D3DXVECTOR3(0.0f, 0.15f, 0.0f);

	velUD = 5.0f;
	velLR = 5.0f;

	mass = 5.0f;

	//textureName = "RedGhostTexture.JPEG";
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
	movement->setPosition(position);
>>>>>>> origin/MartinezWorking
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->SetOrientation( 0.0f);
	movement->SetRotation( 0.0f);
	movement->SetLinear( D3DXVECTOR4(0, 0, 0, 0));

	// Initial state of the enemy
	State = Wander;
<<<<<<< HEAD
}

// Update the enemy
void Enemy_Base::Update( float dt )
{
=======

	shape = 3;

	// Create the texture
	render->LoadTexture( textureName, textureNumber);

	// create 3D mesh from .x file
	render->LoadMesh( meshName, &objectMesh);
}

// Update the enemy
void Enemy_Base::Update( float dt, D3DXVECTOR4 playerPosition )
{
	playerPos = playerPosition;

>>>>>>> origin/MartinezWorking
	if ( health <= 0)
	{
		isDead = true;
	}

<<<<<<< HEAD
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
=======
	UpdateState( State, dt );
	movement->GetNewOrientation();
	movement->Update(dt);

	//havokMovement();

	/*havokShape->position = movement->GetPosition();
	havokShape->Update(dt);*/
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
>>>>>>> origin/MartinezWorking
			// ChangeState ( Attack );
			break;
		}
	};
}

<<<<<<< HEAD
void Enemy_Base::Render()
{
	model->setPosition( movement->GetPosition());
	model->render( device );
=======
void Enemy_Base::Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat)
{
	//enemyGun->mPSys->draw(hwnd);

	render->Render3DObject( position, objectMesh, veiwMat, projMat);
}


void Enemy_Base::createHavokObject(hkpWorld* world)
{
	// Create Object Based on Shape
	switch(shape)
	{
		case PLAYERSPHERE:
			createSphereObject(world);
			break;

		case PLAYERBOX:
			createBoxObject(world);
			break;

		case 3:
			createCapsuleObject(world);
			break;

		case PLAYERNONE:
			createCapsuleObject(world);
			break;
	}
}

void Enemy_Base::createSphereObject(hkpWorld* world)
{
	// Create a temp body info
	hkpCharacterRigidBodyCinfo	bodyInfo;

	// Sphere Parameters
	hkReal radius = (scale.x + scale.z) / 2;

	// Create Sphere Based on Parameters
	hkpSphereShape* sphereShape = new hkpSphereShape(radius);

	// Set The Object's Properties
	bodyInfo.m_shape = sphereShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_friction = 1.0f;

	// Calculate Mass Properties
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(sphereShape, mass, massProperties);
	
	// Set Mass Properties

	// Create Rigid Body
	objectBody = new hkpCharacterRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	sphereShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(objectBody->getRigidBody());
}

void Enemy_Base::createBoxObject(hkpWorld* world)
{
	// Create a temp body info
	hkpCharacterRigidBodyCinfo	bodyInfo;

	// Box Parameters
	hkVector4 halfExtents(scale.x, scale.y, scale.z);

	// Create Box Based on Parameters
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);

	// Calculate Mass Properties
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, mass, massProperties);

	// Set Mass Properties
	bodyInfo.m_mass = 100.0f;

	// Create Rigid Body
	objectBody = new hkpCharacterRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	boxShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(objectBody->getRigidBody());
}

void Enemy_Base::createCapsuleObject(hkpWorld* world)
{
	// Create a temp body info
	hkpCharacterRigidBodyCinfo	bodyInfo;

	// Capsule Parameters
	hkVector4	vertexA(scale.x, position.y + (scale.y / 2), scale.z, 0);	// Top
	hkVector4	vertexB(scale.x, position.y - (scale.y / 2), scale.z, 0);	// Bottom
	hkReal		radius	=	(scale.x + scale.z) / 2;						// Radius

	// Create Capsule Based on Parameters
	hkpCapsuleShape* capsuleShape = new hkpCapsuleShape(vertexA, vertexB, radius);

	// Set The Object's Properties
	bodyInfo.m_shape = capsuleShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);


	// Calculate Mass Properties
	hkMassProperties massProperties;

	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(capsuleShape, mass, massProperties);
	
	// Create Rigid Body
	objectBody = new hkpCharacterRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	capsuleShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(objectBody->getRigidBody());
}

void Enemy_Base::havokMovement()
{
	hkpCharacterOutput output;

	if(movement->GetPosition().x < objectBody->getPosition().getComponent(0))
	input.m_inputLR += velLR;
	else if(movement->GetPosition().x > objectBody->getPosition().getComponent(0))
	input.m_inputLR -= velLR;

	if(movement->GetPosition().z < objectBody->getPosition().getComponent(2))
	input.m_inputUD += velUD;
	else if(movement->GetPosition().z > objectBody->getPosition().getComponent(2))
	input.m_inputUD -= velUD;

	input.m_wantJump = false;
	input.m_atLadder = false;
	
	input.m_up = hkVector4(0, 1, 0);
	input.m_forward.set(0, 0, 1);
	
	hkStepInfo stepInfo;
	stepInfo.m_deltaTime = 1.0f / 60.0f;
	stepInfo.m_invDeltaTime = 1.0f / (1.0f / 60.0f);

	input.m_stepInfo = stepInfo;
	input.m_characterGravity.set(0, -16, 0);
	input.m_velocity = objectBody->getRigidBody()->getLinearVelocity();
	input.m_position = objectBody->getRigidBody()->getPosition();

	objectBody->checkSupport(stepInfo, input.m_surfaceInfo);

	context->update(input, output);

	objectBody->setLinearVelocity(output.m_velocity, 1.0f / 60.0f);
>>>>>>> origin/MartinezWorking
}