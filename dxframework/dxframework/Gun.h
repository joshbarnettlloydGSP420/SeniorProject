
#include "DirectXFramework.h"
#include "InputManager.h"
#include <crtdbg.h>

#include <list>
#include <vector>
#include <ctime>

#include "CameraObj.h"
//#include "PSystem.h"

class Gun : public PSystem
{
public:
	Gun(const LPCWSTR fxName, 
		const std::string& techName, 
		const LPCWSTR texName, 
		const D3DXVECTOR3& accel, 
		const AABB& box,
		int maxNumParticles,
		float timePerParticle)
		: PSystem(fxName, techName, texName, accel, box, maxNumParticles,
		timePerParticle)
	{}  //empty constructor

	void initParticle(Particle& out, D3DXVECTOR3 pos)
	{
		// Generate at camera. OR GENERATE AT ANY WANTED POINT 
		out.initialPos = pos;

		// Set down a bit so it looks like player is carrying the gun.
		out.initialPos.x += 0.8f;              
		out.initialPos.y -= 0.7f;
		out.initialPos.z += 3.0f;

		// Fire in camera's look direction.
		float speed = 50.0f;
		out.initialVelocity = speed*gCamera->look();


		out.initialTime      = mTime;
		out.lifeTime        = 4.0f;
		out.initialColor    = WHITE;
		out.initialSize     = 10.0f; //GetRandomFloat(10.0f, 11.0f);  **** use this if we want to have different size bullets for what ever reason
		out.mass            = 1.0f;
	}


};



