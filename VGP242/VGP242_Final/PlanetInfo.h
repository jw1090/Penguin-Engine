#pragma once
#include <PenguinEngine/Inc/PenguinEngine.h>

using namespace PenguinEngine::Math;
using namespace PenguinEngine::Graphics;

class PlanetInfo
{
public:
	explicit PlanetInfo(Texture* texture, Vector3 distanceFromCenter, float scale, float rotationSpeed, float revolutionSpeed);

	void Update(float deltaTime);
	void InitializeTexture(const std::filesystem::path& fileName);
	void TerminateTexture();
	void BindPS(uint32_t slot);
	void Render();

	const Vector3 GetDistanceFromCenter() { return mDistanceFromCenter; }
	const float GetScale() { return mScale; }
	const float GetRotation() { return mRotation; }
	const float GetRevolution() { return mRevolution; }

	void SetMeshBuffer(MeshBuffer& meshBuffer) { mMeshBuffer = meshBuffer; }
private:
	Texture* mDiffuseMap;
	MeshBuffer mMeshBuffer;
	Vector3 mDistanceFromCenter = Vector3::Zero;
	float mScale = 1.0f;
	float mRotationSpeed = 0.0f;
	float mRotation = 0.0f;
	float mRevolutionSpeed = 0.0f;
	float mRevolution = 0.0f;
};