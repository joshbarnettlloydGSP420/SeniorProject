#include "LightManager.h"

LightManager::LightManager(LPDIRECT3DDEVICE9 device)
{
	//save the device for future use
	myDevice = device;
	//Turn on lighting
	myDevice->SetRenderState(D3DRS_LIGHTING,   TRUE);
}

LightManager::~LightManager()
{

}

int LightManager::createLight()
{

	D3DLIGHT9 *newLight = new D3DLIGHT9;
	
	newLight->Type							= D3DLIGHT_DIRECTIONAL;
	newLight->Ambient						= D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	newLight->Diffuse						= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	newLight->Specular						= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	newLight->Position						= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	newLight->Range							= 5.0f;
	newLight->Attenuation0					= 0.0f;
	newLight->Attenuation1					= 0.05f;
	newLight->Attenuation2					= 0.0f;

	
	//push the light onto our light vector
	lights.push_back((D3DLIGHT9*) newLight);

	//set and enable the light
	myDevice->SetLight((int)lights.size()-1, (D3DLIGHT9 *)lights[((int)lights.size()-1)]);
	myDevice->LightEnable((int)lights.size()-1, true);

	return ((int)lights.size() - 1);

}

void LightManager::enableLight(int lightNumber)
{
    myDevice->LightEnable(lightNumber , TRUE);
}

void LightManager::disableLight(int lightNumber)
{
	myDevice->LightEnable(lightNumber , FALSE);
}

void LightManager::setDiffuse(int lightNumber, float r, float g, float b)
{
	lights[lightNumber]->Diffuse.r = r;
	lights[lightNumber]->Diffuse.g = g;
	lights[lightNumber]->Diffuse.b = b;
	//after we change the light we need to reset it.
	myDevice->SetLight(lightNumber, (D3DLIGHT9 *)lights[lightNumber]);
}

void LightManager::setSpecular(int lightNumber, float r, float g, float b){
	lights[lightNumber]->Specular.r = r;
	lights[lightNumber]->Specular.g = g;
	lights[lightNumber]->Specular.b = b;
	//after we change the light we need to reset it.
	myDevice->SetLight(lightNumber, (D3DLIGHT9 *)lights[lightNumber]);
}

void LightManager::setAmbient(int lightNumber, float r, float g, float b){
	lights[lightNumber]->Ambient.r = r;
	lights[lightNumber]->Ambient.g = g;
	lights[lightNumber]->Ambient.b = b;
	//after we change the light we need to reset it.
	myDevice->SetLight(lightNumber, (D3DLIGHT9 *)lights[lightNumber]);
}

void LightManager::setPosition(int lightNumber, D3DXVECTOR3 newPosition){
	lights[lightNumber]->Position = newPosition;
	//after we change the light we need to reset it.
	myDevice->SetLight(lightNumber, (D3DLIGHT9 *)lights[lightNumber]);
}

void LightManager::setRange(int lightNumber, float newRange){
	lights[lightNumber]->Range = newRange;
	//after we change the light we need to reset it.
	myDevice->SetLight(lightNumber, (D3DLIGHT9 *)lights[lightNumber]);
}
