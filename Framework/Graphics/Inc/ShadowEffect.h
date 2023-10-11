#pragma once

#include "Camera.h"
#include "ConstantBuffer.h"
#include "LightType.h"
#include "PixelShader.h"
#include "RenderTarget.h"
#include "VertexShader.h"

namespace PenguinEngine::Graphics
{
	class RenderObject;

	class ShadowEffect
	{
	public:
		void Initialize();
		void Terminate();

		void Begin();
		void End();

		void Render(const RenderObject& renderObject);

		void SetDirectionalLight(const DirectionalLight& directionalLight);

		void SetFocus(const Math::Vector3& focusPosition) { mFocusPosition = focusPosition; }
		void SetSize(float size) { mSize = size; }

		const Camera& GetLightCamera() const { return mLightCamera; }
		const Texture& GetDepthMap() const { return mDepthMapRenderTarget; }

		void DebugUI();

	private:
		void UpdateLightCamera();

		struct TransformData
		{
			Math::Matrix4 wvp;
		};

		using TransformBuffer = TypedConstantBuffer<TransformData>;

		Camera mLightCamera;

		const DirectionalLight* mDirectionalLight = nullptr;

		VertexShader mVertexShader;
		PixelShader mPixelShader;

		TransformBuffer mTransformBuffer;

		RenderTarget mDepthMapRenderTarget;

		Math::Vector3 mFocusPosition = Math::Vector3::Zero;
		float mSize = 100.0f;
	};
}