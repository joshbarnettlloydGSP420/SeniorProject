#include "Game.h"


Game::Game(void)
{
}


Game::~Game(void)
{
}

void Game::Init( InputManager* input, IDirect3DDevice9* m_pD3DDevice, HWND* hWnd  )
{
	device = m_pD3DDevice;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Creating Camera																						 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	camera = new Camera();
	camera->create(m_pD3DDevice, -100.0, 0.00, hWnd);
	camera->setLookAt(D3DXVECTOR3(0.0f,0.0f,0.0f));
	camera->setPosition(D3DXVECTOR3(0.0f,20.0f,-15.0f));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Lighting																						 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	light = new LightManager( device );
	int light_one = light->createLight();
	light->setPosition( light_one, D3DXVECTOR3( 0.0f, 0.0f, 10.0f));
	light->setRange( light_one, 200.0f);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Font COM Object																				 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// create a FONT object
	//D3DXCreateFont(device, 30, 0, FW_BOLD, 0, false, 
	//	DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
	//	DEFAULT_PITCH | FF_DONTCARE, TEXT("Delicious-Roman"), 
	//	&m_pD3DFont);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create 3D Mesh From X																				 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Load Test Mesh
	model_house = new Model();
	model_house->loadModel(device, "House.x");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Player and Enemies																			 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// create player
	player = new Player();

	// create enemy
	enemy = new Enemy_Base();
	enemy->Init( m_pD3DDevice );

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create Havok Object																					 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Havok
	havok = new HavokCore(true);

	// Locking is necessary to make sure no two threads are trying to change the world at the same time
	havok->getWorld()->lock();

	player->Init( havok );
	//createGroundBox(havok->getWorld());	

	havok->getWorld()->unlock();
}

void Game::Update( float dt )
{
	havok->stepSimulation(dt);
	player->Update(dt);
}

void Game::Render()
{
	//////////////////////////////////////////////////////////////////////////
	// If the device was not created successfully, return 
	//////////////////////////////////////////////////////////////////////////
	if(!device)
		return;

	device->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,125,255),1.0f,0);
	//////////////////////////////////////////////////////////////////////////
	// Draw 3D Objects
	//////////////////////////////////////////////////////////////////////////
	//model_house->setPosition( D3DXVECTOR3( 0, 0, 0));
	//model_house->setScale( D3DXVECTOR3( 0.005, 0.005, 0.005));
	//model_house->render(device);

	enemy->Render();

	// Clear the back buffer, call BeginScene()
	device->BeginScene();

	//////////////////////////////////////////////////////////////////////////
	// Draw 2D sprites
	//////////////////////////////////////////////////////////////////////////
	//m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// End drawing 2D sprites
	//m_pD3DSprite->End();

	// EndScene, and Present the back buffer to the display buffer
	device->EndScene();
	device->Present(NULL, NULL, NULL, NULL);
}

//void Game::createGroundBox(hkpWorld* world)
//{
	// Create a ground area
	//hkVector4 halfExtents(20.0f, 2.0f, 30.0f);
	//hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set its properties
	//hkpRigidBodyCinfo ci;
	//ci.m_shape = boxShape;
	//ci.m_position = hkVector4(0.0f, 0.0f, 0.0f);
	//ci.m_motionType = hkpMotion::MOTION_FIXED;

	// Create the rigid body
	//hkpRigidBody* rigidBody = new hkpRigidBody(ci);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	//boxShape->removeReference();

	// Remove reference and add the rigidbody to the world
	//world->addEntity(rigidBody)->removeReference();

//}

void Game::Shutdown()
{
	// Texture
	//SAFE_RELEASE(m_pTexture)

	// Sprite
	//SAFE_RELEASE(m_pD3DSprite);

	// Font
	//SAFE_RELEASE(m_pD3DFont);

}