#pragma once

#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "RenderTarget.h"
#include "Sampler.h"
#include "VertexShader.h"

namespace PenguinEngine::Graphics
{
	class RenderObject;
	class Texture;

	class GaussianBlurEffect
	{
	public:
		void Initialize();
		void Terminate() ;

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void SetSourceTexture(const Texture& texture) { mSourceTexture = &texture; }

		const Texture& GetHorizontalBlurTexture() const { return mHorizontalBlurRenderTarget; }
		const Texture& GetVerticalBlurTexture() const { return mVerticalBlurRenderTarget; }
		const Texture& GetResultTexture() const { return mVerticalBlurRenderTarget; }

		int& BlurIterations() { return mBlurIterations; }
		float& BlurSaturation() { return mBlurSaturation;  }

	private:
		struct SettingsData
		{
			float screenWidth;
			float screenHeight;
			float multiplier;
			float padding;
		};

		using SettingsBuffer = TypedConstantBuffer<SettingsData>;

		RenderTarget mHorizontalBlurRenderTarget;
		RenderTarget mVerticalBlurRenderTarget;

		VertexShader mVertexShader;
		PixelShader mHorizontalBlurPixelShader;
		PixelShader mVerticalBlurPixelShader;

		SettingsBuffer mSettingsBuffer;

		Sampler mSampler;

		const Texture* mSourceTexture = nullptr;

		int mBlurIterations = 1;
		float mBlurSaturation = 1.0f;
	};
}