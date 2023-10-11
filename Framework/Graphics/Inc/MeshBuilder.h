#pragma once

#include "MeshTypes.h"

namespace PenguinEngine::Graphics
{
	class MeshBuilder
	{
	public:
		static MeshPC CreateCubePC(float size);
		static MeshPC CreateCubePC(float size, Color color);
		static MeshPC CreateCubePC(float size, Color color1, Color color2);
		static MeshPC CreateCubePC(float size, Color color1, Color color2, Color color3, Color color4);

		static MeshPC CreatePlanePC(int columns, int rows, float spacing);
		static MeshPC CreatePlanePC(int columns, int rows, float spacing, Color color);

		static MeshPC CreateCylinderPC(int slices, int rings);

		static MeshPC CreateSpherePC(int slices, int rings, float radius);
		static MeshPC CreateSpherePC(int slices, int rings, float radius, Color color);

		static MeshPC CreateDonutPC(int slices, int rings, float radius);
		static MeshPX CreateCubePX(float size);
		static MeshPX CreateSkyBox(float size);

		static MeshPX CreateSpherePX(int slices, int rings, float radius);
		static MeshPX CreateSkySpherePX(int slices, int rings, float radius);
		static MeshPX CreateScreenQuad();

		static Mesh CreatePlane(int columns, int rows, float spacing);
		static Mesh CreateSphere(int slices, int rings, float radius);
		static Mesh CreateSkySphere(int slices, int rings, float radius);

	private:
		static void CreateCapVerticesPC(MeshPC& mesh, int rows, int& colorIndex);

		static void CubeIndices(MeshPC& mesh);
		static void PlaneIndices(MeshPC& mesh, int columns, int rows);
		static void PlaneIndices(MeshPX& mesh, int columns, int rows);
		static void PlaneIndices(Mesh& mesh, int columns, int rows);
		static void CreateCapIndices(MeshPC& mesh, int columns, int rows);
	};
}