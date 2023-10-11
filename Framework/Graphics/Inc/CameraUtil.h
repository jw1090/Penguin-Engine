#pragma once

#include "Camera.h"

namespace PenguinEngine::Graphics
{
	class CameraUtil
	{
	public:
		Math::Matrix4 RenderReflection(Camera camera, float height);
	};
}