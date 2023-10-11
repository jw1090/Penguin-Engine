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

	PenguinEngine::Graphics::RenderGroup mCharacter;
	PenguinEngine::Graphics::RenderObject mGroundRenderObject;

	// draw skeleton
	// draw mesh
	float mFPS = 0.0f;
	bool mPause = false;
};