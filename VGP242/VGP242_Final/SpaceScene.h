#include <PenguinEngine/Inc/PenguinEngine.h>

#include "PlanetInfo.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Input;

class SpaceScene : public PenguinEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	Camera mCamera;

	VertexShader mVertexShader;
	PixelShader mPixelShader;

	ConstantBuffer mConstantBuffer;

	Sampler mSampler;

	MeshBuffer mSkyBoxMeshBuffer;
	MeshBuffer mPlanetMeshBuffer;

	MeshPX mSkyBoxMesh;
	MeshPX mPlanetMesh;

	std::vector<PlanetInfo> planets;
	std::unique_ptr<Texture> mSkyboxTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mSunTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mMercuryTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mVenusTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mEarthTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mMarsTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mJupiterTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mSaturnTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mUranusTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mNeptuneTexture = std::make_unique<Texture>();
	std::unique_ptr<Texture> mPlutoTexture = std::make_unique<Texture>();

	void InitializePlanets();
	void RenderPlanets();

	void CameraControl(float deltaTime);
};