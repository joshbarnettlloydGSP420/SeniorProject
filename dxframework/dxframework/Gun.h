
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
	Gun(const std::string& fxName, 
		const std::string& techName, 
		const std::string& texName, 
		const D3DXVECTOR3& accel, 
		const AABB& box,
		int maxNumParticles,
		float timePerParticle)
		: PSystem(fxName, techName, texName, accel, box, maxNumParticles,
		timePerParticle)
	{}  //empty constructor

	void initParticle(Particle& out)
	{
		// Generate at camera. OR GENERATE AT ANY WANTED POINT
		out.initialPos = gCamera->pos() + D3DXVECTOR3(0.0f, 3.5f, 0.0f);

		// Set down a bit so it looks like player is carrying the gun.
		out.initialPos.y -= 3.0f;

		// Fire in camera's look direction.
		float speed = 500.0f;
		out.initialVelocity = speed*gCamera->look();


		out.initialTime      = mTime;
		out.lifeTime        = 4.0f;
		out.initialColor    = WHITE;
		out.initialSize     = GetRandomFloat(80.0f, 90.0f);
		out.mass            = 1.0f;
	}


};



