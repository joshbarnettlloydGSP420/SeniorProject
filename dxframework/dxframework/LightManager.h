#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>

#include <vector>


class LightManager
{
public:
	LightManager(LPDIRECT3DDEVICE9 device);
	~LightManager();
	void enableLight(int lightNumber);
	void disableLight(int lightNumber);

	//creates a light and returns the light number;
	int createLight(); //Create a new point light

	void setDiffuse(int lightNumber, float r, float g, float b);
	void setSpecular(int lightNumber, float r, float g, float b);
	void setAmbient(int lightNumber, float r, float g, float b);
	void setPosition(int lightNumber, D3DXVECTOR3 newPosition);
	void setRange(int lightNumber, float newRange);

private:
	std::vector <D3DLIGHT9 *> lights;
	LPDIRECT3DDEVICE9 myDevice;

	D3DLIGHT9 light2;

};