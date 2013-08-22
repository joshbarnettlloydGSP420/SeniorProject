// Global Constants
// We need to set these variables from our application
float4x4 worldViewProjectionMatrix;	// Transfroms positions to view space
float4x4 worldInverseTransposeMatrix; // Transforms normals to world space
float4x4 worldMatrix; // The world matrix of this object

float3 eyePos;	// eye position of the camera

// Light information (Point Light)
float3 lightPos; // light position
float3 ambientLight; // ambient light color
float3 diffuseLight; // diffuse light color
float3 specularLight; // specular light color
float3 lightAttenuation; // light attenuation

// Material information
float4 ambientMaterial; // ambient material color
float4 diffuseMaterial; // diffuse material color
float4 specularMaterial; // specular material color
float specularPower; // specular power exponent

// Texture
texture tex;	// texture

// Texture sampler state
sampler texSampler = sampler_state
{
	texture = tex;
	// Tri-linear filtering
	MinFilter = linear;
	MagFilter = linear;
	MipFilter = linear;
};

struct VS_OUT
{
	float4 posH : POSITION0;	// vertex position in homogenous clip space
	float3 normW : TEXCOORD0;	// vertex normal in world space
	float3 posW : TEXCOORD1;	// vertex position in world space
	float2 tex0 : TEXCOORD2;	// vertex UV texture coordinate #0
};

// vertex shader function
VS_OUT VS(float3 pos : POSITION0, float3 norm : NORMAL0, float2 tex0 : TEXCOORD0)
{
	VS_OUT vsOut = (VS_OUT) 0;

	// transform the vertex position to homogenous
	vsOut.posH = mul(float4(pos, 1.0f), worldViewProjectionMatrix);

	// transform vertex position to world space
	vsOut.posW = mul(float4(pos, 1.0f), worldMatrix).xyz;

	// transform vertex normal to world space
	vsOut.normW =  mul(float4(norm, 1.0f), worldInverseTransposeMatrix).xyz;

	// Normalize the normals after translating into world space
	vsOut.normW = normalize(vsOut.normW);

	// pass the texture coordinate (UV) to the pixel shader without modifiers
	vsOut.tex0 = tex0;

	return vsOut;
}

// pixel shade function
float4 PS(VS_OUT vsOut) : COLOR
{
	// get the texel from the texture map that gets mapped to this pixel
	float3 texColor = tex2D(texSampler, vsOut.tex0);

	// Interpolated normals can "un-normalize", so we re-normalize them
	vsOut.normW = normalize(vsOut.normW);

	// compute the view vector, from the pixel to the eye position (v)
	float3 toEye = normalize(eyePos - vsOut.posW);

	// comput the light direction vector from the pixel to the light (L)
	float3 lightDir = normalize(lightPos - vsOut.posW);

	/// Phong Specualr calculation
	// Compute the reflection vector
	//float3 R = reflect(-lightDir, vsOut.normW);
	//float T = pow(max(dot(R, toEye), 0), specularPower);

	/// Blinn-Phong Specular Calculation
	// compute the half vector
	float3 H = normalize(lightDir + toEye);
	float T = pow(max(dot(H, vsOut.normW), 0), specularPower);

	// determine the diffuse light intensity
	float S = max(dot(lightDir, vsOut.normW), 0);

	// compute ambient diffuse and specular terms seperately
	float3 spec = T * (specularMaterial * specularLight).rgb;
	float3 diff = S * (diffuseMaterial * diffuseLight * texColor).rgb;
	float3 ambi = (ambientMaterial * ambientLight * texColor).rgb;

	// Compute attenuation
	float d = distance(lightPos, vsOut.posW);
	float A = lightAttenuation.x + lightAttenuation.y * d + lightAttenuation.z * d * d;

	// sum all of the terms together and copy the diffuse alpha channel
	return float4(ambi + (diff + spec) / A, diffuseMaterial.a);
}

// technique (and associated passes)
technique tech0
{
	pass p0
	{
		// specify the vertex and pixel shader association with this pass
		VertexShader = compile vs_3_0 VS(); // Vertex shader model 3.0
		PixelShader = compile ps_3_0 PS(); // Pixel shader model 3.0

		// Example of setting render states in an effect file
		// This example allows us to use alpha blending (transparency)
		//AlphaBlendEnable = true;
		//SrcBlend = SrcAlpha;
		//DestBlend = InvSrcAlpha;
		//BlendOp = Add;
	}
}