#include <PenguinEngine/Inc/PenguinEngine.h>

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

	PenguinEngine::Graphics::Camera mCamera;
	PenguinEngine::Graphics::DirectionalLight mDirectionalLight;

	PenguinEngine::Graphics::StandardEffect mStandardEffect;
	PenguinEngine::Graphics::WaterEffect mWaterEffect;
	PenguinEngine::Graphics::WaterEffect mReflectionEffect;

	PenguinEngine::Graphics::RenderObject mSkyboxRenderObject;
	PenguinEngine::Graphics::RenderObject mGroundRenderObject;
	PenguinEngine::Graphics::RenderObject mWaterRenderObject;
	PenguinEngine::Graphics::RenderObject mReflectionRenderObject;
	PenguinEngine::Graphics::RenderObject mDuckRenderObject;

	float mRunningTime = 0.0f;

	float mFPS = 0.0f;
	bool mPause = false;

	float mWaterWeight = 0.8f;
};