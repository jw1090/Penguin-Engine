#pragma once

// Engine headers
#include <Core/Inc/Core.h>
#include <Math/Inc/PenguinEngineMath.h>

// DirextX headers
#include <d3d11_1.h>
#include <d3dcompiler.h>

// External headers
#include <ImGui/Inc/imgui.h>

// DirectX libraries
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

template <class T>
inline void SafeRelease(T*& ptr)
{
	if (ptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}