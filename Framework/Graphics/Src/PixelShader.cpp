#include "Precompiled.h"
#include "PixelShader.h"

#include "GraphicsSystem.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void PixelShader::Initialize(const std::filesystem::path& filePath, const char* entryPoint)
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;
	ID3DBlob* shaderBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		filePath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entryPoint, "ps_5_0",
		shaderFlags, 0, &shaderBlob, &errorBlob);
	if (errorBlob && errorBlob->GetBufferPointer())
		LOG("%s", static_cast<const char*>(errorBlob->GetBufferPointer()));
	ASSERT(SUCCEEDED(hr), "PixelShader -- Failed to compile pixel shader");

	auto device = GraphicsSystem::Get()->GetDevice();
	hr = device->CreatePixelShader(
		shaderBlob->GetBufferPointer(),
		shaderBlob->GetBufferSize(),
		nullptr,
		&mPixelShader);
	ASSERT(SUCCEEDED(hr), "PixelShader -- Failed to create pixel shader.");

	SafeRelease(shaderBlob);
	SafeRelease(errorBlob);
}

void PixelShader::Terminate()
{
	SafeRelease(mPixelShader);
}

void PixelShader::Bind()
{
	auto context = GraphicsSystem::Get()->GetContext();

	context->PSSetShader(mPixelShader, nullptr, 0);
}