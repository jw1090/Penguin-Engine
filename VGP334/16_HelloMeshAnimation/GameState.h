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

	PenguinEngine::Graphics::RenderGroup mJolleen;
	PenguinEngine::Graphics::ModelID mJolleenModelID;
	PenguinEngine::Graphics::Animator mJolleenAnimator;

	PenguinEngine::Graphics::RenderObject mGroundRenderObject;

	bool mDrawSkeleton = false;
	float mFPS = 0.0f;
	bool mPause = false;
};