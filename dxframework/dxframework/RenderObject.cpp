#include "RenderObject.h"


RenderObject::RenderObject(void)
{
	textureNum = 0;
}


RenderObject::~RenderObject(void)
{
}

void RenderObject::Init( IDirect3DDevice9* device, ID3DXSprite* m_pD3DSprite )
{
	this->device = device;
	spriteObject = m_pD3DSprite;
}

void RenderObject::MaterialSettings()
{
	ZeroMemory(&m_pMaterial[0], sizeof(m_pMaterial[0]));

	m_pMaterial[0].Ambient				= D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_pMaterial[0].Diffuse				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMaterial[0].Emissive				= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pMaterial[0].Specular				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMaterial[0].Power				= 30.0f;
}

void RenderObject::CreateVertexElement()
{
		D3DVERTEXELEMENT9 elems[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	//device->CreateVertexDeclaration( elems, &d3dVertexDecl );
}

void RenderObject::LoadTexture( LPCSTR fileName, int textureNum )
{
	this->textureNum = textureNum;

	//D3DXCreateSprite(device, &spriteObject);

	// create a TEXTURE object
	D3DXCreateTextureFromFileEx(device, fileName , 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &m_pTexture[textureNum]);
}

void RenderObject::LoadShaderEffects(LPCSTR fileName, int fxNum )
{
	// Toon Effects Shader
	ID3DXBuffer* ErrorMessage = 0;
	D3DXCreateEffectFromFile(device,
		fileName,
		0,
		0,
		D3DXSHADER_DEBUG,
		0,
		&fx[0],
		&ErrorMessage);

	if( ErrorMessage )
	{
		char error[512];
		ZeroMemory( error, 256 );
		strcpy_s( error, (char*)ErrorMessage->GetBufferPointer() );
		MessageBox(0, (LPCSTR)error, "Shader Error", MB_OK );
	}

	hTech[0] = fx[0]->GetTechniqueByName("tech0");
}

void RenderObject::Render3DObject(D3DXVECTOR4 position, Mesh* objectMesh, D3DXMATRIX	viewMat, D3DXMATRIX projMat)
{

	//////////////////////////////////////////////////////////////////////////
	// Draw 3D Objects
	//////////////////////////////////////////////////////////////////////////
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixIdentity(&transMat);

	//device->SetStreamSource(0, mesh_vb, 0, sizeof(Vertex));
	//device->SetIndices(mesh_ib);
	//device->SetVertexDeclaration(d3dVertexDecl);

	fx[0]->SetTechnique(hTech[0]);

	UINT numPasses = 0;
	fx[0]->Begin(&numPasses, 0);

	for(UINT i = 0; i < numPasses; ++i)
	{
		fx[0]->BeginPass(i);

		// Mesh Matrix
		D3DXMatrixScaling(&scaleMat, 0.15f, 0.15f, 0.15f);
		D3DXMatrixRotationYawPitchRoll(&rotMat, 0.0f, 0.0f, 0.0f);
		D3DXMatrixTranslation(&transMat, position.x, position.y, position.z);
		//D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
		//D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);
		D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

		D3DXMatrixInverse(&invTransMat, 0, &worldMat);
		D3DXMatrixTranspose(&invTransMat, &invTransMat);

		D3DXMATRIX wvp = worldMat * viewMat * projMat;
		D3DXMATRIX wvpit;
		D3DXMatrixInverse(&wvpit, 0, &wvp);
		D3DXMatrixTranspose(&wvpit, &wvpit);

		fx[0]->SetMatrix("WVP", &wvp);
		fx[0]->SetMatrix("WVPIT", &wvpit);
		fx[0]->SetMatrix("World", &worldMat);
		fx[0]->SetMatrix("View", &viewMat);
		fx[0]->SetMatrix("Projection", &projMat);
		fx[0]->SetMatrix("WorldInverseTranspose", &invTransMat);

		fx[0]->SetTexture("gTexture", m_pTexture[textureNum]);
		fx[0]->CommitChanges();
		objectMesh->p_Mesh->DrawSubset(0);

		fx[0]->EndPass();
	}
	fx[0]->End();
}

void RenderObject::Render2DSprite(int textureNum )
{
	// Set Transform
	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);

	D3DXMatrixScaling(&scaleMat, 1.0f, 1.0f, 0.0f);
	D3DXMatrixRotationZ(&rotMat, D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&transMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

	// Set Transform for the object m_pD3DSprite
	spriteObject->SetTransform(&worldMat);

	spriteObject->Draw(m_pTexture[textureNum], 0, &D3DXVECTOR3(m_imageInfo.Width * 0.5f, 
			m_imageInfo.Height * 0.5f, 0.0f), 0,
			D3DCOLOR_ARGB(255, 255, 255, 255));
}

void RenderObject::LoadMesh(LPCSTR fileName, Mesh** meshObject)
{
	// Create a Temp Mesh
	Mesh* temp = new Mesh();

	// Load Mesh to Temp
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, device, &adjBuffer, &matBuffer, &effBuffer, &temp->numMaterials, &temp->p_Mesh);

	// Vertex Declarations
	D3DVERTEXELEMENT9 elems[65];
	UINT numElems = 0;
	d3dVertexDecl->GetDeclaration( elems, &numElems );

	ID3DXMesh* t = 0;

	temp->p_Mesh->CloneMesh( D3DXMESH_MANAGED, elems, m_pD3DDevice, &t );
	temp->p_Mesh->Release();
	temp->p_Mesh = t;

	temp->p_Mesh->Optimize(D3DXMESH_MANAGED,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0,
		&temp->p_Mesh);

	// Compute Normals (Doesn't Always Look Good)
	//D3DXComputeNormals( temp->p_Mesh, NULL );

	// Check for Materials already in the Mesh
	if( matBuffer )
	{
		D3DXMATERIAL* mat = (D3DXMATERIAL*)matBuffer->GetBufferPointer();
		temp->textures.clear();
		temp->textures.reserve( temp->numMaterials );

		short nummaterials = temp->GetNumMaterials();

		for( short i = 0; i < temp->GetNumMaterials(); ++i )
		{
			temp->textures.push_back( NULL );

			if( mat[i].pTextureFilename != 0 )
			{
				D3DXCreateTextureFromFileA( device, (LPCSTR)mat[i].pTextureFilename, &temp->textures[i] );
			}
		}
	}
	// Else it will just appear black (with Toon Shading)

	// Load Mesh Object with the temp variables
	*meshObject = temp;
}