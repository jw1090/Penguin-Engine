#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Math;
using namespace PenguinEngine::Math::Constants;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] =
		{
			Colors::Red,
			Colors::Green,
			Colors::Orange,
			Colors::Blue,
			Colors::Magenta,
			Colors::Cyan,
			Colors::LightGray,
			Colors::GreenYellow,
			Colors::LightSalmon,
			Colors::SpringGreen,
			Colors::Yellow,
			Colors::Firebrick
		};

		index %= std::size(colorTable);

		return colorTable[index++];
	}
}

#pragma region PC

#pragma region Cube PC

MeshPC MeshBuilder::CreateCubePC(float size)
{
	int colorIndex = 0;

	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, GetNextColor(colorIndex) }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, GetNextColor(colorIndex) }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, GetNextColor(colorIndex) }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, GetNextColor(colorIndex) }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, GetNextColor(colorIndex) }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, GetNextColor(colorIndex) }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, GetNextColor(colorIndex) }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, GetNextColor(colorIndex) }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color)
{
	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, color }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, color }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, color }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, color }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, color }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, color }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, color }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, color }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color1, Color color2)
{
	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, color1 }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, color2 }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, color1 }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, color2 }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, color2 }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, color1 }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, color2 }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, color1 }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, Color color1, Color color2, Color color3, Color color4)
{
	MeshPC mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, color1 }); // Top Right    - 0
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, color2 }); // Bottom Right - 1
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, color3 }); // Bottom Left  - 2
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, color4 }); // Top Left     - 3

	// BACK
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, color3 }); // Top Right    - 4
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, color4 }); // Bottom Right - 5
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, color1 }); // Bottom Left  - 6
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, color2 }); // Top Left     - 7

	CubeIndices(mesh);

	return mesh;
}

#pragma endregion

#pragma region Plane PC

MeshPC MeshBuilder::CreatePlanePC(int columns, int rows, float spacing)
{
	int colorIndex = 0;

	MeshPC mesh;
	const float halfHeight = rows * spacing * 0.5f;
	const float halfWidth = columns * spacing * 0.5f;

	// Add Vertices
	for (int i = 0; i < rows + 1; ++i)
	{
		for (int j = 0; j < columns + 1; ++j)
		{
			mesh.vertices.push_back
			({
				Vector3
				{
					(j * spacing) - halfWidth,
					0,
					(i * spacing) - halfHeight
				},
				GetNextColor(colorIndex) });
		}
	}

	PlaneIndices(mesh, columns + 1, rows + 1);

	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int columns, int rows, float spacing, Color color)
{
	MeshPC mesh;
	const float halfHeight = rows * spacing * 0.5f;
	const float halfWidth = columns * spacing * 0.5f;

	// Add Vertices
	for (int i = 0; i < rows + 1; ++i)
	{
		for (int j = 0; j < columns + 1; ++j)
		{
			mesh.vertices.push_back
			({
				Vector3
				{
					(j * spacing) - halfWidth,
					0,
					(i * spacing) - halfHeight
				},
				color
			});
		}
	}

	PlaneIndices(mesh, columns + 1, rows +1);

	return mesh;
}

#pragma endregion

#pragma region Cylinder PC

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
	int colorIndex = 0;
	
	MeshPC mesh;
	const float halfHeight = rings * 0.5f;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / rings);

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					sin(rotation),
					ring - halfHeight,
					-cos(rotation),
				},
				GetNextColor(colorIndex)
			});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	CreateCapVerticesPC(mesh, rings, colorIndex);
	CreateCapIndices(mesh, slices, rings);

	return mesh;
}

#pragma endregion

#pragma region Sphere PC

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
	int colorIndex = 0;

	MeshPC mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi),
				},
				GetNextColor(colorIndex)
			});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius, Color color)
{
	MeshPC mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi),
				},
				color
			});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

#pragma endregion

MeshPC MeshBuilder::CreateDonutPC(int slices, int rings, float radius)
{
	int colorIndex = 0;

	MeshPC mesh;
	const float halfHeight = radius * 0.5f;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float ringRadius = sin(r / (rings - 1) * Pi) * radius;
		float phi = ring * (Pi / rings);

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			mesh.vertices.push_back
			({
				Vector3
				{
					sin(rotation) * ringRadius,
					radius * cos(phi) * sin(ringRadius),
					cos(rotation) * ringRadius,
				}
			, GetNextColor(colorIndex)
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

void MeshBuilder::CreateCapVerticesPC(MeshPC& mesh, int rows, int& colorIndex)
{
	const float halfHeight = rows * 0.5f;

	mesh.vertices.push_back
	({
		Vector3
		{
			0.0f,
			0.0f - halfHeight,
			0.0f,
		}
	, GetNextColor(colorIndex)
	});

	mesh.vertices.push_back
	({
		Vector3
		{
			0.0f,
			rows - 1.0f - halfHeight,
			0.0f,
		}
	, GetNextColor(colorIndex)
	});
}

#pragma endregion

#pragma region PX

MeshPX MeshBuilder::CreateCubePX(float size)
{
	MeshPX mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2(0, 1) }); // Top Right Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2(1, 1) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(1, 0) }); // Bottom Left Close

	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2(0, 1) }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(1, 0) }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0, 0) }); // Top Left Close

	// BACK
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2(0, 1) }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(1, 1) }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(1, 0) }); // Bottom Right Far

	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2(0, 1) }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(1, 0) }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0, 0) }); // Top Right Far

	// RIGHT
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0, 1) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(1, 1) }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2(1, 0) }); // Bottom Right Close

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0, 1) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2(1, 0) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2(0, 0) }); // Top Right Close

	// Left
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0, 1) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(1, 1) }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(1, 0) }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0, 1) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(1, 0) }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2(0, 0) }); // Top Left Far

	// Top
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0, 1) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2(1, 1) }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(1, 0) }); // Top Left Close

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0, 1) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(1, 0) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2(0, 0) }); // Top Left Far

	// Bottom
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2(0, 1) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(1, 1) }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(1, 0) }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2(0, 1) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(1, 0) }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(0, 0) }); // Bottom Left Close

	int i = 0;
	for (const auto& vertex : mesh.vertices)
	{
		mesh.indices.push_back(i);
		++i;
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSkyBox(float size)
{
	MeshPX mesh;

	// FRONT
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2( 0.5f, 0.33f) }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(0.25f, 0.66f) }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2( 0.5f, 0.66f) }); // Bottom Right Close

	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2( 0.5f, 0.33f) }); // Top Right Close
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0.25f, 0.33f) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(0.25f, 0.66f) }); // Bottom Left Close

	// BACK
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2( 1.0f, 0.33f) }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(0.75f, 0.66f) }); // Bottom Right Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2( 1.0f, 0.66f) }); // Bottom Left Far

	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2( 1.0f, 0.33f) }); // Top Left Far
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0.75f, 0.33f) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(0.75f, 0.66f) }); // Bottom Right Far

	// RIGHT
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0.75f, 0.33f) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2( 0.5f, 0.66f) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2(0.75f, 0.66f) }); // Bottom Right Far

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2(0.75f, 0.33f) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2( 0.5f, 0.33f) }); // Top Right Close
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2( 0.5f, 0.66f) }); // Bottom Right Close

	// Left
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0.25f, 0.33f) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2( 0.0f, 0.66f) }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(0.25f, 0.66f) }); // Bottom Left Close

	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0.25f, 0.33f) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2( 0.0f, 0.33f) }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2( 0.0f, 0.66f) }); // Bottom Left Far

	// Top
	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2( 0.5f,  0.0f) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0.25f, 0.33f) }); // Top Left Close
	mesh.vertices.push_back({ Vector3{  size,  size, -size }, Vector2( 0.5f, 0.33f) }); // Top Right Close

	mesh.vertices.push_back({ Vector3{  size,  size,  size }, Vector2( 0.5f,  0.0f) }); // Top Right Far
	mesh.vertices.push_back({ Vector3{ -size,  size,  size }, Vector2(0.25f,  0.0f) }); // Top Left Far
	mesh.vertices.push_back({ Vector3{ -size,  size, -size }, Vector2(0.25f, 0.33f) }); // Top Left Close

	// Bottom
	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2( 0.5f, 0.66f) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(0.25f,  1.0f) }); // Bottom Left Far
	mesh.vertices.push_back({ Vector3{  size, -size,  size }, Vector2( 0.5f,  1.0f) }); // Bottom Right Far

	mesh.vertices.push_back({ Vector3{  size, -size, -size }, Vector2( 0.5f, 0.66f) }); // Bottom Right Close
	mesh.vertices.push_back({ Vector3{ -size, -size, -size }, Vector2(0.25f, 0.66f) }); // Bottom Left Close
	mesh.vertices.push_back({ Vector3{ -size, -size,  size }, Vector2(0.25f,  1.0f) }); // Bottom Left Far

	int i = 0;
	for (const auto& vertex : mesh.vertices)
	{
		mesh.indices.push_back(i);
		++i;
	}

	return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
	MeshPX mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi),
				},
				Vector2{u, v}
			});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

MeshPX MeshBuilder::CreateSkySpherePX(int slices, int rings, float radius)
{
	MeshPX mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			mesh.vertices.push_back
			({
				Vector3
				{
					radius * cos(rotation) * sin(phi),
					radius * cos(phi),
					radius * sin(rotation) * sin(phi),
				},
				Vector2{u, v}
			});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
	MeshPX mesh;
	mesh.vertices.push_back({ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
	mesh.vertices.push_back({ { -1.0f, +1.0f, 0.0f }, { 0.0f, 0.0f } });
	mesh.vertices.push_back({ { +1.0f, +1.0f, 0.0f }, { 1.0f, 0.0f } });
	mesh.vertices.push_back({ { +1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });
	mesh.indices = { 0, 1, 2, 0, 2, 3 };
	return mesh;
}

#pragma endregion

#pragma region Standard

Mesh MeshBuilder::CreatePlane(int columns, int rows, float spacing)
{
	int colorIndex = 0;

	Mesh mesh;

	const float halfHeight = rows * spacing * 0.5f;
	const float halfWidth = columns * spacing * 0.5f;

	// Add Vertices
	for (int i = 0; i < rows + 1; ++i)
	{
		float r = static_cast<float>(i);

		for (int j = 0; j < columns + 1; ++j)
		{
			float s = static_cast<float>(j);

			float uStep = 1.0f / (columns);
			float vStep = 1.0f / (rows);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			const float x = (j * spacing) - halfWidth;
			const float y = 0.0f;
			const float z = (r * spacing) - halfHeight;
			const Vector3 p = { x, 0.0f, z };
			const Vector3 n = Math::Vector3::YAxis;
			const Vector3 t = Math::Vector3::XAxis;

			mesh.vertices.push_back
			({
				p, n, t,
				Vector2{u, v}
			});
		}
	}

	PlaneIndices(mesh, columns + 1, rows + 1);

	return mesh;
}

Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
	Mesh mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings ; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			const float x = radius * sin(rotation) * sin(phi);
			const float y = radius * cos(phi);
			const float z = radius * cos(rotation) * sin(phi);
			const Vector3 p = { x, y, z };
			const Vector3 n = Normalize(p);
			const Vector3 t = Normalize({-z, 0.0f, x});

			mesh.vertices.push_back
			({
				p, n, t,
				Vector2{u, v}
			});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

Mesh MeshBuilder::CreateSkySphere(int slices, int rings, float radius)
{
	Mesh mesh;

	// Add Side Vertices
	for (int ring = 0; ring < rings; ++ring)
	{
		float r = static_cast<float>(ring);
		float phi = r * (Pi / (rings - 1));

		for (int slice = 0; slice < slices + 1; ++slice)
		{
			float s = static_cast<float>(slice);
			float rotation = (s / (slices)) * TwoPi;

			float uStep = 1.0f / (slices);
			float vStep = 1.0f / (rings);
			float u = 1.0f - (uStep * s);
			float v = 0.0f + (vStep * r);

			const float x = radius * - sin(rotation)* sin(phi);
			const float y = radius * cos(phi);
			const float z = radius * cos(rotation) * sin(phi);
			const Vector3 p = { x, y, z };
			const Vector3 n = Normalize(p);
			const Vector3 t = Normalize({ -z, 0.0f, x });

			mesh.vertices.push_back
			({
				p, n, t,
				Vector2{u, v}
				});
		}
	}

	PlaneIndices(mesh, slices + 1, rings);

	return mesh;
}

#pragma endregion

#pragma	region Indices

void MeshBuilder::CubeIndices(MeshPC& mesh)
{
	mesh.indices =
	{
		// Front & Back
		0, 1, 2,
		3, 0, 2,
		4, 6, 5,
		4, 7, 6,

		// Left & Right
		3, 2, 6,
		7, 3, 6,
		4, 5, 1,
		4, 1, 0,

		// Top & Bottom
		0, 3, 7,
		0, 7, 4,
		1, 5, 6,
		1, 6, 2
	};
}

void MeshBuilder::PlaneIndices(MeshPC& mesh, int columns, int rows)
{
	for (int i = 0; i < rows - 1; ++i)
	{
		for (int j = 0; j < columns - 1; ++j)
		{
			const int bottomLeftIndex = (i * columns) + j;

			// Triangle 1
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);

			// Triangle 2
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);
			mesh.indices.push_back(bottomLeftIndex + 1);
		}
	}
}

void MeshBuilder::PlaneIndices(MeshPX& mesh, int columns, int rows)
{
	for (int i = 0; i < rows - 1; ++i)
	{
		for (int j = 0; j < columns - 1; ++j)
		{
			const int bottomLeftIndex = (i * columns) + j;

			// Triangle 1
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);

			// Triangle 2
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);
			mesh.indices.push_back(bottomLeftIndex + 1);
		}
	}
}

void MeshBuilder::PlaneIndices(Mesh& mesh, int columns, int rows)
{
	for (int i = 0; i < rows - 1; ++i)
	{
		for (int j = 0; j < columns - 1; ++j)
		{
			const int bottomLeftIndex = (i * columns) + j;

			// Triangle 1
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);

			// Triangle 2
			mesh.indices.push_back(bottomLeftIndex);
			mesh.indices.push_back(bottomLeftIndex + columns + 1);
			mesh.indices.push_back(bottomLeftIndex + 1);
		}
	}
}

void MeshBuilder::CreateCapIndices(MeshPC& mesh, int columns, int rows)
{
	const int bottomVertex = columns * rows + rows;
	const int topVertex = columns * rows + rows + 1;

	for (int i = 0; i < rows - 1; ++i)
	{
		if (i == 0)
		{

			for (int j = 0; j < columns; ++j)
			{
				const int bottomLeftIndex = (i * columns) + j;

				mesh.indices.push_back(bottomLeftIndex);
				mesh.indices.push_back(bottomLeftIndex + 1);
				mesh.indices.push_back(bottomVertex);
			}
		}
		if (i == rows - 2)
		{
			for (int j = 0; j < columns; ++j)
			{
				const int bottomLeftIndex = (i * columns) + j;

				mesh.indices.push_back(bottomLeftIndex + columns + rows - 1);
				mesh.indices.push_back(topVertex);
				mesh.indices.push_back(bottomLeftIndex + columns + rows);
			}
		}
	}
}

#pragma endregion