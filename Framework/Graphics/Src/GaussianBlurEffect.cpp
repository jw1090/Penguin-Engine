#include "Precompiled.h"
#include "GaussianBlurEffect.h"

#include "Camera.h"
#include "GraphicsSystem.h"
#include "RenderObject.h"
#include "VertexTypes.h"

using namespace PenguinEngine;
using namespace PenguinEngine::Graphics;

void GaussianBlurEffect::Initialize()
{
	auto graphicsSystem = GraphicsSystem::Get();
	const auto screenWidth = graphicsSystem->GetBackBufferWidth();
	const auto screenHeight = graphicsSystem->GetBackBufferHeight();
	mHorizontalBlurRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);
	mVerticalBlurRenderTarget.Initialize(screenWidth, screenHeight, RenderTarget::Format::RGBA_U8);

	mVertexShader.Initialize<VertexPX>("../../Assets/Shaders/GaussianBlur.fx");
	mHorizontalBlurPixelShader.Initialize("../../Assets/Shaders/GaussianBlur.fx", "HorizontalBlurPS");
	mVerticalBlurPixelShader.Initialize("../../Assets/Shaders/GaussianBlur.fx", "VerticalBlurPS");

	mSettingsBuffer.Initialize();

	mSampler.Initialize(Sampler::Filter::Linear, Sampler::AddressMode::Wrap);
}

void GaussianBlurEffect::Terminate()
{
	mSampler.Terminate();

	mSettingsBuffer.Terminate();

	mVerticalBlurPixelShader.Terminate();
	mHorizontalBlurPixelShader.Terminate();
	mVertexShader.Terminate();

	mVerticalBlurRenderTarget.Terminate();
	mHorizontalBlurRenderTarget.Terminate();
}

void GaussianBlurEffect::Begin()
{
	mVertexShader.Bind();

	auto graphicsSystem = GraphicsSystem::Get();
	const auto screenWidth = graphicsSystem->GetBackBufferWidth();
	const auto screenHeight = graphicsSystem->GetBackBufferHeight();

	SettingsData settingsData;
	settingsData.screenWidth = static_cast<float>(screenWidth);
	settingsData.screenHeight = static_cast<float>(screenHeight);
	settingsData.multiplier = mBlurSaturation;
	mSettingsBuffer.Update(settingsData);
	mSettingsBuffer.BindPS(0);

	mSampler.BindPS(0);
}

void GaussianBlurEffect::End()
{
	auto graphicsSystem = GraphicsSystem::Get();
	graphicsSystem->ResetRenderTarget();
	graphicsSystem->ResetViewport();
}

void GaussianBlurEffect::Render(const RenderObject& renderObject)
{
	auto graphicsSystem = GraphicsSystem::Get();

	// Horizontal blur
	mHorizontalBlurRenderTarget.BeginRender();
	mSourceTexture->BindPS(0);
	mHorizontalBlurPixelShader.Bind();
	renderObject.meshBuffer.Render();
	Texture::UnbindPS(0);
	mHorizontalBlurRenderTarget.EndRender();

	for (int i = 1; i < mBlurIterations; ++i)
	{
		// Vertical blur
		mVerticalBlurRenderTarget.BeginRender();
		mHorizontalBlurRenderTarget.BindPS(0);
		mVerticalBlurPixelShader.Bind();
		renderObject.meshBuffer.Render();
		Texture::UnbindPS(0);
		mVerticalBlurRenderTarget.EndRender();

		// Horizontal blur
		mHorizontalBlurRenderTarget.BeginRender();
		mVerticalBlurRenderTarget.BindPS(0);
		mHorizontalBlurPixelShader.Bind();
		renderObject.meshBuffer.Render();
		Texture::UnbindPS(0);
		mHorizontalBlurRenderTarget.EndRender();
	}

	// Vertical blur
	mVerticalBlurRenderTarget.BeginRender();
	mHorizontalBlurRenderTarget.BindPS(0);
	mVerticalBlurPixelShader.Bind();
	renderObject.meshBuffer.Render();
	Texture::UnbindPS(0);
	mVerticalBlurRenderTarget.EndRender();
}