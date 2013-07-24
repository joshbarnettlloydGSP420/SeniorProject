#include "Object_Base.h"


Object_Base::Object_Base(void)
{
	objectMesh = new Mesh();
	position = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	mass = 5.0f;
	shape = BOX;

	velUD = 0.0f;
	velLR = 0.0f;
}


Object_Base::~Object_Base(void)
{
}

void Object_Base::Update(float deltaTime)
{
	convertPosition();
	
	objectBody->getRigidBody()->setLinearVelocity(velocityCalc(deltaTime));

}

void Object_Base::convertPosition()
{
	position.x = (float)bodyInfo.m_position.getComponent(0);
	position.y = (float)bodyInfo.m_position.getComponent(1);
	position.z = (float)bodyInfo.m_position.getComponent(2);
	position.w = (float)bodyInfo.m_position.getComponent(3);
}

// Changes the velocity in Havok based on velocityUD and velocityLR
hkVector4 Object_Base::velocityCalc(float dt)
{
	hkVector4 tempVel;

	tempVel.set(velLR, velUD, velUD, dt);

	return tempVel;
}

// This is a switch that will auto create an Havok Object based on its shape
void Object_Base::createHavokObject(hkpWorld* world)
{
	// Create Object Based on Shape
	switch(shape)
	{
		case SPHERE:
			createSphereObject(world);
			stateMachineInit();
			break;

		case BOX:
			createBoxObject(world);
			stateMachineInit();
			break;

		case CAPSULE:
			createCapsuleObject(world);
			stateMachineInit();
			break;

		case NONE:
			createBoxObject(world);
			stateMachineInit();
			break;
	}
}

void Object_Base::createSphereObject(hkpWorld* world)
{
	// Sphere Parameters
	hkReal radius = (scale.x + scale.z) / 2;

	// Create Sphere Based on Parameters
	hkpSphereShape* sphereShape = new hkpSphereShape(radius);

	// Set The Object's Properties
	bodyInfo.m_shape = sphereShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	bodyInfo.m_friction = 1.0f;
	bodyInfo.m_restitution = 0.2f;


	// Calculate Mass Properties
	hkMassProperties massProperties;

	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(sphereShape, mass, massProperties);
	
	// Set Mass Properties
	bodyInfo.setMassProperties(massProperties);

	// Create Rigid Body
	objectBody = new hkpRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	sphereShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(objectBody->getRigidBody());
}

void Object_Base::createBoxObject(hkpWorld* world)
{
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
	bodyInfo.m_mass(100.0f);

	// Create Rigid Body
	objectBody = new hkpCharacterRigidBody(&bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	boxShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(objectBody->getRigidBody());
}

void Object_Base::createCapsuleObject(hkpWorld* world)
{
	// Capsule Parameters
	hkVector4	vertexA(position.x, position.y + (scale.y / 2), position.z, 0);	// Top
	hkVector4	vertexB(position.x, position.y - (scale.y / 2), position.z, 0);	// Bottom
	hkReal		radius	=	(scale.x + scale.z) / 2;							// Radius

	// Create Capsule Based on Parameters
	hkpCapsuleShape* capsuleShape = new hkpCapsuleShape(vertexA, vertexB, radius);

	// Set The Object's Properties
	bodyInfo.m_shape = capsuleShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;

	// Calculate Mass Properties
	hkMassProperties massProperties;

	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(capsuleShape, mass, massProperties);
	
	// Set Mass Properties
	bodyInfo.setMassProperties(massProperties);

	// Create Rigid Body
	objectBody = new hkpRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	capsuleShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(objectBody->getRigidBody());
}

void Object_Base::stateMachineInit()
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