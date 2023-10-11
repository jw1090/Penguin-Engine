#include <PenguinEngine/Inc/PenguinEngine.h>

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Math;

class PlaneState : public PenguinEngine::AppState
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

	MeshPC mPlaneMesh;
	MeshBuffer mMeshBuffer;

	bool isColored = true;
};