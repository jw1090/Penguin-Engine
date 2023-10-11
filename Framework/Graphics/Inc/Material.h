#pragma once

#include "Colors.h"

namespace PenguinEngine::Graphics
{
	struct Material
	{
		Color ambient = Colors::Black;
		Color diffuse = Colors::Black;
		Color specular = Colors::Black;
		Color emissive = Colors::Black;
		float power = 0.0f;
		float padding[3] = { 0.0f };
	};
}