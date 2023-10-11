#include "Precompiled.h"
#include "TransformComponent.h"

using namespace PenguinEngine;

void TransformComponent::DebugUI()
{
    Graphics::SimpleDraw::AddTransform(GetMatrix4());
}