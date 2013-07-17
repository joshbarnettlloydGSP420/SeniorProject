#include "model.h"


Model::Model(void)
{
	mesh = NULL;
}

Model::~Model(void)
{
	// Delete the model
	if (mesh){
		mesh->Release();
	}
	
	// Delete the material buffer
	if (materialBuffer)
		//materialBuffer->Release();

	// Delete the materials
	if (materials){
		delete[] materials;
	}

	// Delete the textures
	if (textures){
		delete[] textures;
	}
}

bool Model::loadModel(LPDIRECT3DDEVICE9 device, LPCSTR filename){
	HRESULT hr;

	scale = D3DXVECTOR3(1.0f, 1.0f , 1.0f); //set our scale variable to 1
	position = D3DXVECTOR4(0.0f, 0.0f, 0.0f , 0.0f); //set the position to 0,0,0
	rotation = D3DXVECTOR3(0.0f, 0.0f , 0.0f); //set the rotation, to nothing.
	
	//load the model, and its material information
	hr = D3DXLoadMeshFromX(filename, 
					  D3DXMESH_SYSTEMMEM, //Location to store our model
					  device, //The d3d Device
					  NULL,
					  &materialBuffer, //a pointer to the materials loaded by the mesh
					  NULL,
					  &materialCount, //number of material sets
					  &mesh);

	if FAILED(hr){
		return false;
	}

	//get the pointer to the material buffer
	D3DXMATERIAL* modelMaterials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
    
    //Create arrays to hold the textures and materials
    materials = new D3DMATERIAL9[materialCount];
	textures  = new LPDIRECT3DTEXTURE9[materialCount];
    
	// for each of our materials load the material and texture into our arrays.
    for(DWORD i = 0; i < materialCount; i++)
    {
		
        //store the material in our array
        materials[i] = modelMaterials[i].MatD3D;

		// Load the texture
		if (modelMaterials[i].pTextureFilename != NULL)
		{
			hr = D3DXCreateTextureFromFile( device, (LPCSTR)modelMaterials[i].pTextureFilename, &textures[i] );
		} else {
			textures[i] = NULL;
		}
    }

	// Delete the material buffer
	if (materialBuffer){
		materialBuffer->Release();
	}

	return true;
}

void Model::render(LPDIRECT3DDEVICE9 device)
{
	DWORD i;

	//set the scale matrix
	D3DXMatrixScaling(&scaleMatrix, scale.x,scale.y,scale.z);

	// store the position information into the translation matrix
	D3DXMatrixTranslation(&transMatrix, position.x, position.y, position.z);

	// set the rotation matrix
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix,rotation.x,rotation.y,rotation.z);

	// Multiply the translation matrix by the rotation matrix, store the result in the translation matrix
	D3DXMatrixMultiply(&transMatrix, &rotationMatrix, &transMatrix);
	// Multiply the translation matrix by the scale matrix,  store the result in the translation matrix
	D3DXMatrixMultiply(&transMatrix, &scaleMatrix, &transMatrix);
	
	// Position the object for rendering based on the position, rotation and scaleing.
	device->SetTransform(D3DTS_WORLD, &transMatrix);

	//render the object
	for(i = 0; i < materialCount; i++ )
    {
        // Set the material 
		device->SetMaterial( &materials[i] );
		// Set the texture if we have one
		if (textures[i]!= NULL){
	        device->SetTexture( 0, textures[i] );
		} else {
			device->SetTexture( 0, NULL );
		}
        // Draw the subset
		mesh->DrawSubset( i );
	}
}

void Model::setPosition(D3DXVECTOR4 positionVector){
	position = positionVector;
}

void Model::changePosition(D3DXVECTOR4 changeVector)
{
	position = position + changeVector;
}

void Model::setRotation(D3DXVECTOR3 rotationVector){
	rotation = rotationVector;
}

void Model::setScale(D3DXVECTOR3 scaleVector){
	scale = scaleVector;
}
