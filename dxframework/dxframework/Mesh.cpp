#include "Mesh.h"


Mesh::Mesh(void)
{
}


Mesh::~Mesh(void)
{
}

void Mesh::ComputeWorld(void)
{
	// Create Temp Meshes for Translating
	D3DXMATRIX	transMat, rotMat, scaleMat;

	// Mesh Matrix
	D3DXMatrixScaling(&scaleMat, 0.025f, 0.025f, 0.025f);
	D3DXMatrixRotationYawPitchRoll(&rotMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&transMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&world, &scaleMat, &transMat);
}

void Mesh::Init( LPCSTR fileName, IDirect3DDevice9* m_pD3DDevice)
{
	device = m_pD3DDevice;

	// create a vertex format
	D3DVERTEXELEMENT9 elems[65] =
	{
		{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	m_pD3DDevice->CreateVertexDeclaration( elems, &d3dVertexDecl );

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Load Shader Effects																					 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Toon Effects Shader
	ID3DXBuffer* ErrorMessage = 0;
	D3DXCreateEffectFromFile(m_pD3DDevice,
		"ToonColored.fx",
		0,
		0,
		D3DXSHADER_DEBUG,
		0,
		&fx[0],
		&ErrorMessage);
	if( ErrorMessage )
	{
		char error[256];
		ZeroMemory( error, 256 );
		strcpy_s( error, (char*)ErrorMessage->GetBufferPointer() );
		MessageBox(0, (LPCSTR)error, "Shader Error", MB_OK );
	}

	hTech[0] = fx[0]->GetTechniqueByName("ToonColored");

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create 3D Mesh From X																				 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////


	// Load Mesh to Temp
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, device, &adjBuffer, &matBuffer, &effBuffer, &numMaterials, &p_Mesh);

	// Vertex Declarations
	//D3DVERTEXELEMENT9 elems[65];
	UINT numElems = 0;
	d3dVertexDecl->GetDeclaration( elems, &numElems );

	ID3DXMesh* t = 0;

	p_Mesh->CloneMesh( D3DXMESH_MANAGED, elems, device, &t );
	p_Mesh->Release();
	p_Mesh = t;

	p_Mesh->Optimize(D3DXMESH_MANAGED,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0,
		&p_Mesh);

	// Compute Normals (Doesn't Always Look Good)
	//D3DXComputeNormals( temp->p_Mesh, NULL );

	// Check for Materials already in the Mesh
	if( matBuffer )
	{
		D3DXMATERIAL* mat = (D3DXMATERIAL*)matBuffer->GetBufferPointer();
		textures.clear();
		textures.reserve( numMaterials );

		for( short i = 0; i < numMaterials; ++i )
		{
			textures.push_back( NULL );

			if( mat[i].pTextureFilename != 0 )
			{
				D3DXCreateTextureFromFileA( device, (LPCSTR)mat[i].pTextureFilename, &textures[i] );
			}
		}
	}
	// Else it will just appear black (with Toon Shading)
}
void Mesh::Render()
{
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixIdentity(&transMat);

	
	//device->SetStreamSource(0, mesh_vb, 0, sizeof(Vertex));
	//device->SetIndices(mesh_ib);
	device->SetVertexDeclaration(d3dVertexDecl);

	fx[0]->SetTechnique(hTech[0]);

	UINT numPasses = 0;
	fx[0]->Begin(&numPasses, 0);

	for(UINT i = 0; i < numPasses; ++i)
	{
		fx[0]->BeginPass(i);


		// Mesh Matrix
		D3DXMatrixScaling(&scaleMat, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&rotMat, 0.0f, 0.0f, 0.0f);
		D3DXMatrixTranslation(&transMat, 100, 100,100);
		D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
		D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

		D3DXMatrixInverse(&invTransMat, 0, &worldMat);
		D3DXMatrixTranspose(&invTransMat, &invTransMat);

		fx[0]->SetMatrix("World", &worldMat);
		fx[0]->SetMatrix("View", &viewMat);
		fx[0]->SetMatrix("Projection", &projMat);
		fx[0]->SetMatrix("WorldInverseTranspose", &invTransMat);

		for( short e = 0; e < numMaterials; ++e )
		{
			fx[0]->SetTexture("gTexture", textures[e]);
			fx[0]->CommitChanges();
			p_Mesh->DrawSubset(e);
		}

		fx[0]->EndPass();
	}
	fx[0]->End();
}