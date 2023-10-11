#pragma once

#include "Colors.h"

using namespace PenguinEngine::Math;

namespace PenguinEngine::Graphics
{
	class Camera;

	namespace SimpleDraw
	{
		void StaticInitialize(uint32_t maxVertexCount);
		void StaticTerminate();

		void AddLine(const Vector3& v0, const Vector3& v1, Color color);
		void AddFace(const Vector3& v0, const Vector3& v1, const Vector3& v2, Color color);

		void AddAABB(const Vector3& min, const Vector3& max, Color color);
		void AddAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, Color color);

		void AddFilledAABB(const Vector3& min, const Vector3& max, Color color);
		void AddFilledAABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, Color color);

		void AddSphere(int slices, int rings, float radius, Color color);

		void AddGroundPlane(float size, Color color);

		void AddTransform(const Matrix4 matrix);

		void Render(const Camera& camera);
	}
}