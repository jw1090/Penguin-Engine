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
	using Handles = std::vector<PenguinEngine::GameObjectHandle>;

	PenguinEngine::GameWorld mGameWorld;
	Handles mHandles;

	bool mPause = false;
};