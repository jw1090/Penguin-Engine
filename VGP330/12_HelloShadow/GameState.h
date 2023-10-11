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
	PenguinEngine::Graphics::ShadowEffect mShadowEffect;

	PenguinEngine::Graphics::RenderObject mBallRenderObject;
	PenguinEngine::Graphics::RenderObject mGroundRenderObject;

	float mBallHeight = 5.0f;
	float mRunningTime = 0.0f;

	float mFPS = 0.0f;
	bool mPause = false;
};