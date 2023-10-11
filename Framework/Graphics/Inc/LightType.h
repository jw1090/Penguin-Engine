#pragma once

#include "Colors.h"

namespace PenguinEngine::Graphics
{
	struct DirectionalLight
	{
		Math::Vector3 direction;
		float padding = 0.0f;
		Color ambient;
		Color diffuse;
		Color specular;
	};
}