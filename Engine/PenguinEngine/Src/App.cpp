#include "Precompiled.h"
#include "App.h"

#include "AppState.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Core;
using namespace PenguinEngine::Graphics;
using namespace PenguinEngine::Input;

void App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		LOG("App -- Next stat: %s", stateName.c_str());
		mNextState = iter->second.get();
	}
}

void App::Run(AppConfig appConfig)
{
	LOG("App -- Running");

	LOG("App -- Creating window...");
	Window window;
	window.Initialize(
		GetModuleHandle(nullptr),
		appConfig.appName,
		appConfig.winWidth,
		appConfig.winHeight);

	LOG("App -- Initalizing engine systems...");
	auto handle = window.GetWindowHandle();
	InputSystem::StaticInitialize(handle);
	GraphicsSystem::StaticInitialize(handle, false);
	SimpleDraw::StaticInitialize(appConfig.debugDrawLimit);
	DebugUI::StaticInitialize(handle, false, true);
	TextureManager::StaticInitialize("../../Assets/");
	ModelManager::StaticInitialize();

	LOG("App -- Initalizing app state...");
	ASSERT(mCurrentState, "App -- No app state found!");
	mCurrentState->Initialize();

	LOG("App -- Entering game loop...");
	mRunning = true;
	while (mRunning)
	{
		window.ProcessMessage();
		if (!window.IsActive())
		{
			Quit();
			continue;
		}

		auto inputSystem = InputSystem::Get();
		inputSystem->Update();

		if (inputSystem->IsKeyPressed(KeyCode::ESCAPE))
		{
			Quit();
			continue;
		}

		if (mNextState)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
		}

		auto deltaTime = TimeUtil::GetDeltaTime();
		mCurrentState->Update(deltaTime);

		auto graphicsSystem = GraphicsSystem::Get();
		graphicsSystem->BeginRender();

		mCurrentState->Render();

		DebugUI::BeginRender();
		mCurrentState->DebugUI();
		DebugUI::EndRender();

		graphicsSystem->EndRender();
	}

	LOG("App -- Terminating app state...");
	mCurrentState->Terminate();

	LOG("App -- Shutting down engine systems...");
	ModelManager::StaticTerminate();
	TextureManager::StaticTerminate();
	DebugUI::StaticTerminate();
	SimpleDraw::StaticTerminate();
	GraphicsSystem::StaticTerminate();
	InputSystem::StaticTerminate();

	LOG("App -- Terminating app window...");
	window.Terminate();
}

void App::Quit()
{
	mRunning = false;
}