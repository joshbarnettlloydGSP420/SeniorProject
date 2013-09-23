
#ifndef PSYSTEM_H
#define PSYSTEM_H

#include "d3dUtil.h"
#include "Vertex.h"
#include <vector>

//===============================================================
class PSystem
{
public:
	PSystem(
		const LPCWSTR fxName, 
		const std::string& techName, 
		const LPCWSTR texName, 
		const D3DXVECTOR3& accel, 
		const AABB& box,
		int maxNumParticles,
		float timePerParticle);

	virtual ~PSystem();

	// Access Methods
	float getTime();
	void  setTime(float t);
	const AABB& getAABB()const;


	void setWorldMtx(const D3DXMATRIX& world);
	void addParticle(D3DXVECTOR3 pos, D3DXVECTOR3 iPos, D3DXVECTOR3 look);

	virtual void onLostDevice();
	virtual void onResetDevice();

	virtual void initParticle(Particle& out,D3DXVECTOR3 pos, D3DXVECTOR3 iPos, D3DXVECTOR3 look) = 0;
	virtual void update(float dt,D3DXVECTOR3 eyePos, D3DXVECTOR3 look);
	virtual void draw(HWND hWnd,D3DXVECTOR3 eyePos, D3DXMATRIX viewProj);
	std::vector<Particle*> getmAliveParticles();

	std::vector<Particle*> mAliveParticles;

protected:
	// In practice, some sort of ID3DXEffect and IDirect3DTexture9 manager should
	// be used so that you do not duplicate effects/textures by having several
	// instances of a particle system.
	ID3DXEffect* mFX;
	D3DXHANDLE mhTech;
	D3DXHANDLE mhWVP;
	D3DXHANDLE mhEyePosL;
	D3DXHANDLE mhTex;
	D3DXHANDLE mhTime;
	D3DXHANDLE mhAccel;
	D3DXHANDLE mhViewportHeight;

	IDirect3DTexture9* mTex;
	IDirect3DVertexBuffer9* mVB;
	D3DXMATRIX mWorld;
	D3DXMATRIX mInvWorld;
	float mTime;
	D3DXVECTOR3 mAccel;
	AABB mBox;
	int mMaxNumParticles;
	float mTimePerParticle;

	std::vector<Particle> mParticles;
	std::vector<Particle*> mDeadParticles; 
};

#endif // P_SYSTEM