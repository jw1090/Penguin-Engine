#include <PenguinEngine/Inc/PenguinEngine.h>

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Math;

class SphereState : public PenguinEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	Camera mCamera;
	
	Texture mEarthTexture;
	Texture mSunTexture;
	MeshPX mSphereMesh;

	VertexShader mVertexShader;
	PixelShader mPixelShader;

	ConstantBuffer mConstantBuffer;

	MeshBuffer mSphereMeshBuffer;

	Sampler mSampler;

	float mRotation1 = 0;
	float mRotation2 = 0;
};