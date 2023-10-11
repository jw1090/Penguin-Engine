// Description: Standard shader for PCEngine.

cbuffer TransformBuffer : register(b0)
{
	matrix world;
	matrix wvp;
	float3 viewPosition;
	float bumpWeight;
}

cbuffer BoneTransformBuffer : register(b1)
{
	matrix boneTransforms[256];
}

cbuffer LightBuffer : register(b2)
{
	float3 lightDirection;
	float4 lightAmbient;
	float4 lightDiffuse;
	float4 lightSpecular;
}

cbuffer MaterialBuffer : register(b3)
{
	float4 materialAmbient;
	float4 materialDiffuse;
	float4 materialSpecular;
	float4 materialEmissive;
	float materialPower;
}

cbuffer SettingBuffer : register(b4)
{
	bool useDiffuseMap;
	bool useSpecularMap;
	bool useBumpMap;
	bool useNormalMap;
	bool useShadowMap;
	bool useSkinning;
	float depthBias;
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D bumpMap : register(t2);
Texture2D normalMap : register(t3);

SamplerState textureSampler : register(s0);

static matrix Identity =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

matrix GetBoneTransform(int4 indices, float4 weights)
{
	if (length(weights) <= 0.0f)
	{
		return Identity;
	}

	matrix transform = boneTransforms[indices[0]] * weights[0];
	transform += boneTransforms[indices[1]] * weights[1];
	transform += boneTransforms[indices[2]] * weights[2];
	transform += boneTransforms[indices[3]] * weights[3];

	return transform;
}

struct VS_INPUT
{
	float3 position : POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 texCoord : TEXCOORD;
	int4 blendIndices : BLENDINDICES;
	float4 blendWeights : BLENDWEIGHT;
};

struct VS_OUTPUT
{
	float4 position : SV_Position;
	float3 worldNormal : NORMAL;
	float3 worldTangent : TANGENT;
	float3 dirToLight : TEXCOORD0;
	float3 dirToView : TEXCOORD1;
	float2 texCoord : TEXCOORD2;
};

VS_OUTPUT VS(VS_INPUT input)
{
	float bumpMapColor = bumpMap.SampleLevel(textureSampler, input.texCoord, 0.0f).r;
	float3 localPosition = input.position;
	if (useBumpMap)
		localPosition += (input.normal * bumpMapColor * bumpWeight);

	VS_OUTPUT output;

	matrix toWorld = world;
	matrix toNDC = wvp;
	if (useSkinning)
	{
		matrix boneTransform = GetBoneTransform(input.blendIndices, input.blendWeights);
		toWorld = mul(boneTransform, toWorld);
		toNDC = mul(boneTransform, toNDC);
	}
	output.position = mul(float4(localPosition, 1.0f), toNDC);
	output.worldNormal = mul(input.normal, (float3x3)toWorld);
	output.worldTangent = mul(input.tangent, (float3x3)toWorld);
	output.dirToLight = -lightDirection;
	output.dirToView = normalize(viewPosition - mul(float4(localPosition, 1.0f), world).xyz);
	output.texCoord = input.texCoord;
	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float3 n = normalize(input.worldNormal);
	float3 t = normalize(input.worldTangent);
	float3 b = normalize(cross(n, t));

	float3 L = normalize(input.dirToLight);
	float3 v = normalize(input.dirToView);

	if (useNormalMap)
	{
		float3x3 tbnw = float3x3(t, b, n);
		float4 normalMapColor = normalMap.Sample(textureSampler, input.texCoord);
		float3 unpackedNormal = normalize(float3((normalMapColor.xy * 2.0f) - 1.0f, normalMapColor.z));
		n = mul(unpackedNormal, tbnw);
	}

	float4 ambient = lightAmbient * materialAmbient;

	float d = saturate(dot(L, n)); // saturate(v) === max(v, 0)
	float4 diffuse = d * lightDiffuse * materialDiffuse;

	float3 r = reflect(-L, n);
	float base = saturate(dot(r, v));
	float s = pow(base, materialPower);
	float4 specular = s * lightSpecular * materialSpecular;

	float4 diffuseMapColor = useDiffuseMap ? diffuseMap.Sample(textureSampler, input.texCoord) : 1.0f;
	float4 specularMapColor = useSpecularMap ? specularMap.Sample(textureSampler, input.texCoord).r : 1.0f;

	float4 finalColor = (ambient + diffuse + materialEmissive) * diffuseMapColor + (specular * specularMapColor);
	return finalColor;
}