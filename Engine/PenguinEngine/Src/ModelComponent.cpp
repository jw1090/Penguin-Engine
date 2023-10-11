#include "Precompiled.h"
#include "ModelComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "RenderService.h"  

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void ModelComponent::Initialize()
{
    auto mm = ModelManager::Get();
    mModelID = mm->GetModelID(mFileName);
    if (mm->GetModel(mModelID) == nullptr)
    {
        mm->LoadModel(mFileName);
        for (const auto& animationFileName : mAnimationFileNames)
        {
            mm->AddAnimation(mModelID, animationFileName);
        }
    }

    auto renderService = GetOwner().GetWorld().GetService<RenderService>();
    renderService->Register(this);
}

void ModelComponent::Terminate()
{
    auto renderService = GetOwner().GetWorld().GetService<RenderService>();
    renderService->Unregister(this);
}