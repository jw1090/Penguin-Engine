#include <PenguinEngine/Inc/PenguinEngine.h>

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;
using namespace PenguinEngine::Math;

class GameState : public PenguinEngine::AppState
{
public:
	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	void CameraControl(float deltaTime);

	Camera mCamera;
	DirectionalLight mDirectionalLight;

	StandardEffect mStandardEffect;
	GaussianBlurEffect mGaussianBlurEffect;
	PostProcessingEffect mPostProcessingEffect;

	RenderTarget mBaseRenderTarget;
	RenderTarget mBloomRenderTarget;

	RenderObject mSunRenderObject;
	RenderObject mEarthRenderObject;
	RenderObject mScreenQuad;

	float mFPS = 0.0f;
	float mEarthOffset = 8.0f;
	float mEarthRotation = 0.0f;
	float mEarthRevolution = 0.0f;
};