#pragma once

namespace PenguinEngine::Graphics::DebugUI
{
	enum class Theme
	{
		Classic,
		Dark,
		Light
	};

	void StaticInitialize(HWND window, bool docking = false, bool multiViewport = false);
	void StaticTerminate();

	void BeginRender();
	void EndRender();
}