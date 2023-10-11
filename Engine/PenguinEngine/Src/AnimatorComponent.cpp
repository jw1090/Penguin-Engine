#include "Precompiled.h"
#include "AnimatorComponent.h"
#include "ModelComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

using namespace PenguinEngine;

void AnimatorComponent::Initialize()
{   
    auto modelComponent = GetOwner().GetComponent<ModelComponent>();
    mAnimator.Initialize(modelComponent->GetModelID());
    mAnimator.PlayAnimation(0, true);
}

void AnimatorComponent::Update(float delatTime)
{
    mAnimator.Update(delatTime);
}

void AnimatorComponent::DebugUI()
{

}