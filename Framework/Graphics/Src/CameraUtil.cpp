#include "Precompiled.h"
#include "CameraUtil.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Math;

Matrix4 CameraUtil::RenderReflection(Camera camera, float height)
{
	Matrix4 mReflectionViewMatrix;

	Vector3 cameraPosition = camera.GetPosition();

	Vector3 position = { cameraPosition.x, cameraPosition.y + (height * 2.0f), cameraPosition.z };
	Vector3 lookAt = camera.GetDirection();

	const Math::Vector3 l = lookAt;
	const Math::Vector3 r = Math::Normalize(Math::Cross(Math::Vector3::YAxis, l));
	const Math::Vector3 u = Math::Normalize(Math::Cross(l, r));
	const float x = -Math::Dot(r, position);
	const float y = -Math::Dot(u, position);
	const float z = -Math::Dot(l, position);

	return
	{
		r.x, u.x, l.x, 0.0f,
		r.y, -u.y, -l.y, 0.0f,
		r.z, -u.z, -l.z, 0.0f,
		x,   y,   z,   1.0f
	};
}