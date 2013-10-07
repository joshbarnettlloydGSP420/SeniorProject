#include "EventManager.h"


EventManager::EventManager(void)
{
	currentRoom = FOYER;
}

EventManager::~EventManager(void)
{

}

void EventManager::spawnEnemies()
{
	// Check the number of enemies and if the player is in the room
}

void EventManager::Init()
{
	// Set Rooms Positions, Scale, then create them
	Foyer.roomPos.set(1.0f, 0.0f, 27.0f, 0.0f);
	Foyer.roomSize.set(21.5f, 20.0f, 22.0f, 0.0f);
	
	
	Ballroom.roomPos.set(-42.0f, 0.0f, 7.5f, 0.0f);
	Ballroom.roomSize.set(21.5, 20.0f, 42.0f, 0.0f);
	
	
	Diningroom.roomPos.set(44.0f, 0.0f, 7.5f, 0.0f);
	Diningroom.roomSize.set(42.5f, 20.0f, 84.0f, 0.0f);
	
	
	Kitchen.roomPos.set(1.0f, 0.0f, -18.0f, 0.0f);
	Kitchen.roomSize.set(21.5f, 20.0f, 22.0f, 0.0f);

	createRooms();
}

void EventManager::Update(float deltaTime)
{
	// Nothing yet, but just incase
}

void EventManager::createRooms()
{
	Foyer.enemiesDead = false;
	Foyer.puzzleSolved = false;
	Foyer.playerInRoom = false;

	hkpRigidBody* rigidBody;
	hkpRigidBodyCinfo bodyInfo;

	// Box Parameters
	hkVector4 halfExtents(Foyer.roomSize);

	// Create Box Based on Parameters
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(Foyer.roomPos.getComponent(0), Foyer.roomPos.getComponent(1), Foyer.roomPos.getComponent(2), Foyer.roomPos.getComponent(3));

	// Create Rigid Body
	rigidBody = new hkpRigidBody(bodyInfo);

	rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.0f, Foyer.boundingArea);

	Ballroom.enemiesDead = false;
	Ballroom.puzzleSolved = false;
	Ballroom.playerInRoom = false;

	// Box Parameters
	halfExtents = Ballroom.roomSize;

	// Create Box Based on Parameters
	 boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(Ballroom.roomPos.getComponent(0), Ballroom.roomPos.getComponent(1), Ballroom.roomPos.getComponent(2), Ballroom.roomPos.getComponent(3));

	// Create Rigid Body
	rigidBody = new hkpRigidBody(bodyInfo);

	rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.0f, Ballroom.boundingArea);

	Diningroom.enemiesDead = false;
	Diningroom.puzzleSolved = false;
	Diningroom.playerInRoom = false;

	// Box Parameters
	halfExtents = Diningroom.roomSize;

	// Create Box Based on Parameters
	boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(Diningroom.roomPos.getComponent(0), Diningroom.roomPos.getComponent(1), Diningroom.roomPos.getComponent(2), Diningroom.roomPos.getComponent(3));

	// Create Rigid Body
	rigidBody = new hkpRigidBody(bodyInfo);

	rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.0f, Diningroom.boundingArea);

	Kitchen.enemiesDead = false;
	Kitchen.puzzleSolved = false;
	Kitchen.playerInRoom = false;

	// Box Parameters
	halfExtents = Kitchen.roomSize;

	// Create Box Based on Parameters
	boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(Kitchen.roomPos.getComponent(0), Kitchen.roomPos.getComponent(1), Kitchen.roomPos.getComponent(2), Kitchen.roomPos.getComponent(3));

	// Create Rigid Body
	rigidBody = new hkpRigidBody(bodyInfo);

	rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.0f, Kitchen.boundingArea);
}

bool EventManager::checkForPlayer(Object_Player* Player)
{
	hkAabb player;

	Player->objectBody->getRigidBody()->getCollidable()->getShape()->getAabb(Player->objectBody->getRigidBody()->getTransform(), 0.0f, player);

	if(Foyer.boundingArea.overlaps(player))
		currentRoom = FOYER;		return true;

	if(Ballroom.boundingArea.overlaps(player))
		currentRoom = BALLROOM;		return true;

	if(Diningroom.boundingArea.overlaps(player))
		currentRoom = DININGROOM;	return true;

	if(Kitchen.boundingArea.overlaps(player))
		currentRoom = KITCHEN;		return true;

	return false;
}