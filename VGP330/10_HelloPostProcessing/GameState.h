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
	InputSystem* mInputSystem;

	RenderTarget mRenderTarget;

	StandardEffect mStandardEffect;
	PostProcessingEffect mPostProcessingEffect;

	Mesh mMesh;
	RenderObject mEarthRenderObject;
	RenderObject mScreenQuad;

	Vector3 mPosition = Vector3::Zero;
	Vector3 mRotation = Vector3::Zero;

	float mRotationAmount = 0.01f;
	bool mAutoRotate = false;

	bool mShowNormals = false;

	float mFPS = 0.0f;
};