#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>

class Model
{
public:
	Model(void);
	virtual ~Model(void);

	bool loadModel(LPDIRECT3DDEVICE9 device, LPCSTR filename);
	void render(LPDIRECT3DDEVICE9 device);
	void setPosition(D3DXVECTOR4 positionVector);
	void changePosition(D3DXVECTOR4 positionVector);
	void setRotation(D3DXVECTOR3 rotationVector);
	void setScale(D3DXVECTOR3 scaleVector);

private:
	LPD3DXMESH mesh; // the model mesh
	DWORD materialCount; // number of materials returned when loading

	LPDIRECT3DTEXTURE9* textures; //a pointer to an array for our textures
	D3DMATERIAL9* materials; //a pointer to an array for our materials
	LPD3DXBUFFER materialBuffer;

	D3DXMATRIX transMatrix;		// the translation matrix
	D3DXMATRIX rotationMatrix;		// the rotation matrix
	D3DXMATRIX scaleMatrix;		// the scale matrix

	D3DXVECTOR3 scale;			//the models scale
	D3DXVECTOR4 position;		//the models position
	D3DXVECTOR3 rotation;		//the models rotation
};
