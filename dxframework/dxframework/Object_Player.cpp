#include "Object_Player.h"
#include "Gun.h"

Object_Player::Object_Player()
{
	objectMesh = new Mesh();
	position = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation = D3DXVECTOR3(0.0f, 0.15f, 0.0f);
	mass = 5.0f;
	shape = PLAYERBOX;

	velUD = 0.0f;
	velLR = 0.0f;

	wantJump = false;
	
	// Initialize the particle system.
	D3DXMATRIX psysWorld;
	D3DXMatrixIdentity(&psysWorld);


	//bullets/gun
	AABB psysBox;
	psysBox.maxPt = D3DXVECTOR3(INFINITY, INFINITY, INFINITY);
	psysBox.minPt = D3DXVECTOR3(-INFINITY, -INFINITY, -INFINITY);
	
	// Accelerate due to gravity.  However, since the bullets travel at 
	// such a high velocity, the effect of gravity of not really observed.
	mPSys = new Gun("gun.fx", "GunTech", "bolt2.dds", D3DXVECTOR3(0, -9.8f, 0), psysBox, 100, -1.0f);
	mPSys->setWorldMtx(psysWorld);              

}


Object_Player::~Object_Player(void)
{

}

void Object_Player::Update(float deltaTime)
{
	convertPosition();
	characterInputOutput();

	//gun update
	mPSys->update(deltaTime);

	if(jumpTimer < 3.2f)
	{
		jumpTimer += deltaTime;
	}
}

void Object_Player::convertPosition()
{
	D3DXVECTOR3 NormRot;

	position.x = (float)objectBody->getPosition().getComponent(0);
	position.y = (float)objectBody->getPosition().getComponent(1);
	position.z = (float)objectBody->getPosition().getComponent(2);
	position.w = (float)objectBody->getPosition().getComponent(3);

	D3DXVec3Normalize(&NormRot, &rotation);

	hk_rotation = hkQuaternion(NormRot.x, NormRot.y, NormRot.z, 0.0f);

}

// Changes the velocity in Havok based on velocityUD and velocityLR
hkVector4 Object_Player::velocityCalc(float dt)
{
	hkVector4 tempVel;

	tempVel.set(velLR, 0.0f, velUD, dt);

	return tempVel;
}

// This is a switch that will auto create an Havok Object based on its shape
void Object_Player::createHavokObject(hkpWorld* world)
{
	// Create Object Based on Shape
	switch(shape)
	{
		case PLAYERSPHERE:
			createSphereObject(world);
			stateMachineInit();
			break;

		case PLAYERBOX:
			createBoxObject(world);
			stateMachineInit();
			break;

		case PLAYERCAPSULE:
			createCapsuleObject(world);
			stateMachineInit();
			break;

		case PLAYERNONE:
			createBoxObject(world);
			stateMachineInit();
			break;
	}
}

void Object_Player::createSphereObject(hkpWorld* world)
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

void Object_Player::createBoxObject(hkpWorld* world)
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

void Object_Player::createCapsuleObject(hkpWorld* world)
{
	// Create a temp body info
	hkpCharacterRigidBodyCinfo	bodyInfo;

	// Capsule Parameters
	hkVector4	vertexA(position.x, position.y + (scale.y / 2), position.z, 0);	// Top
	hkVector4	vertexB(position.x, position.y - (scale.y / 2), position.z, 0);	// Bottom
	hkReal		radius	=	(scale.x + scale.z) / 2;							// Radius

	// Create Capsule Based on Parameters
	hkpCapsuleShape* capsuleShape = new hkpCapsuleShape(vertexA, vertexB, radius);

	// Set The Object's Properties
	bodyInfo.m_shape = capsuleShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_maxSlope = HK_REAL_PI / 3.0f;

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

void Object_Player::stateMachineInit()
{
	manager = new hkpCharacterStateManager();

	// On the Ground
	state = new hkpCharacterStateOnGround();
	manager->registerState(state, HK_CHARACTER_ON_GROUND);
	state->removeReference();

	// In the Air
	state = new hkpCharacterStateInAir();
	manager->registerState(state, HK_CHARACTER_IN_AIR);
	state->removeReference();

	// Jumping
	state = new hkpCharacterStateJumping();
	manager->registerState(state, HK_CHARACTER_JUMPING);
	state->removeReference();

	// Climbing
	state = new hkpCharacterStateClimbing();
	manager->registerState(state, HK_CHARACTER_CLIMBING);
	state->removeReference();

	context = new hkpCharacterContext(manager, HK_CHARACTER_ON_GROUND);
	manager->removeReference();

	// Set the character type
	context->setCharacterType(hkpCharacterContext::HK_CHARACTER_RIGIDBODY);

}

void Object_Player::characterInputOutput()
{
	hkpCharacterInput input;
	hkpCharacterOutput output;

	input.m_inputLR = velLR;
	input.m_inputUD = velUD;

	input.m_wantJump = wantJump;
	input.m_atLadder = false;
	
	input.m_up = hkVector4(0, 1, 0);
	input.m_forward.set(0.0f, 0.0f, D3DXToRadian(rotation.x));
	input.m_forward.setRotatedDir(hk_rotation, input.m_forward);

	if(wantJump && jumpTimer < 3.2)
	{
		input.m_characterGravity.set(0, 16, 0);
		input.m_wantJump = wantJump;
	}
	else
	{
		input.m_characterGravity.set(0, -16, 0);
		input.m_wantJump = false;
	}
	
	hkStepInfo stepInfo;
	stepInfo.m_deltaTime = 1.0f / 60.0f;
	stepInfo.m_invDeltaTime = 1.0f / (1.0f / 60.0f);

	input.m_stepInfo = stepInfo;
	//input.m_characterGravity.set(0, -16, 0);
	input.m_velocity = objectBody->getRigidBody()->getLinearVelocity();
	input.m_position = objectBody->getRigidBody()->getPosition();

	objectBody->checkSupport(stepInfo, input.m_surfaceInfo);

	context->update(input, output);

	objectBody->setLinearVelocity(output.m_velocity, 1.0f / 60.0f);
}

bool Object_Player::collisionCheck(hkpRigidBody* rigidBody)
{
	hkAabb aabbBase;
	hkAabb aabbOut;

	rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.4f, aabbOut);
	objectBody->getRigidBody()->getCollidable()->getShape()->getAabb(objectBody->getRigidBody()->getTransform(), 0.4f, aabbBase);


	if(aabbBase.overlaps(aabbOut))
	{
		return true;
	}

	return false;
}