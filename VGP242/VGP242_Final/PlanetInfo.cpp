#include "PlanetInfo.h"

PlanetInfo::PlanetInfo(Texture* texture, Vector3 distanceFromCenter, float scale, float rotationSpeed, float revolutionSpeed)
	: mDiffuseMap(texture)
	, mDistanceFromCenter(distanceFromCenter)
	, mScale(scale)
	, mRotationSpeed(rotationSpeed)
	, mRevolutionSpeed(revolutionSpeed)
{

}

void PlanetInfo::Update(float deltaTime)
{
	mRevolution += mRevolutionSpeed * deltaTime;
	mRotation += mRotationSpeed * deltaTime;
}

void PlanetInfo::InitializeTexture(const std::filesystem::path& fileName)
{
	mDiffuseMap->Initialize(fileName);
}

void PlanetInfo::TerminateTexture()
{
	mDiffuseMap->Terminate();
}

void PlanetInfo::BindPS(uint32_t slot)
{
	mDiffuseMap->BindPS(slot);
}

void PlanetInfo::Render()
{
	mMeshBuffer.Render();
}