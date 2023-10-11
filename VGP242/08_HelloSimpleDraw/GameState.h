#include <PenguinEngine/Inc/PenguinEngine.h>

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;
using namespace PenguinEngine::Math;

class GameState : public PenguinEngine::AppState
{
public:
	enum class DebugType
	{
		Box,
		FilledBox,
		Sphere,
		Plane,
		Transform
	};

	void Initialize() override;
	void Terminate() override;

	void Update(float deltaTime) override;
	void Render() override;
	void DebugUI() override;

private:
	Camera mCamera;
	InputSystem* mInputSystem;

	Vector3 mPosition1 = Vector3::Zero;
	Vector3 mPosition2 = Vector3::One;
	Color mColor = Colors::White;

	DebugType mCurrentDebug = DebugType::Box;

	void CameraControl(float deltaTime);
};