#include "k2EngineLowPreCompile.h"
#include "Ssr.h"

namespace nsK2EngineLow {
	void Ssr::OnInit(
		RenderTarget& mainRenderTarget,
		RenderTarget& depthRenderTarget,
		RenderTarget& normalRenderTarget
	)
	{
		{
			SpriteInitData initData;
			initData.m_width = 1600;
			initData.m_height = 900;
			initData.m_fxFilePath = "Assets/shader/Ssr.fx";
			initData.m_vsEntryPointFunc = "VSMain";
			initData.m_psEntryPoinFunc = "PSMain";
			initData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
			initData.m_textures[1] = &depthRenderTarget.GetRenderTargetTexture();
			initData.m_textures[2] = &normalRenderTarget.GetRenderTargetTexture();
			initData.m_expandConstantBuffer = &m_ssrCb;
			initData.m_expandConstantBufferSize = sizeof(SsrCb);

			initData.m_alphaBlendMode = AlphaBlendMode_None;
			initData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
			initData.textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_BORDER;

			m_reflectionSprite.Init(initData);
			float clearColor[] = {
				0.0f,0.0f,0.0f,0.0f
			};

			m_reflectionRenderTarget.Create(
				1600,
				900,
				1,
				1,
				mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN,
				clearColor
			);
		}
		m_blur.Init(&m_reflectionRenderTarget.GetRenderTargetTexture(), true);

		SpriteInitData initData;
		initData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		initData.m_textures[1] = &m_blur.GetBokeTexture();
		initData.m_width = mainRenderTarget.GetWidth();
		initData.m_height = mainRenderTarget.GetHeight();
		initData.m_fxFilePath = "Assets/shader/Ssr.fx";
		initData.m_vsEntryPointFunc = "VSMain";
		initData.m_psEntryPoinFunc = "PSMain";
		initData.m_alphaBlendMode = AlphaBlendMode_None;
		initData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

		m_finalSprite.Init(initData);

		m_finalRenderTarget.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			DXGI_FORMAT_UNKNOWN
		);
	}
	void Ssr::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		if (!m_isEnable) {
			return;
		}

		g_graphicsEngine->BeginGPUEvent("SSR");

		//まずは映り込みイメージを作成する
		rc.WaitUntilToPossibleSetRenderTarget(m_reflectionRenderTarget);
		rc.SetRenderTargetAndViewport(m_reflectionRenderTarget);
		rc.ClearRenderTargetView(m_reflectionRenderTarget);

		m_ssrCb.cameraPosInWorld = g_camera3D->GetPosition();
		m_ssrCb.mViewProj = g_camera3D->GetViewProjectionMatrix();
		m_ssrCb.mViewProjInv.Inverse(m_ssrCb.mViewProj);

		m_reflectionSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_reflectionRenderTarget);

		//映り込み画像をブラーでぼかす
		m_blur.ExecuteOnGPU(rc, 2.0f);

		rc.WaitUntilToPossibleSetRenderTarget(m_finalRenderTarget);
		rc.SetRenderTargetAndViewport(m_finalRenderTarget);
		m_finalSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(m_finalRenderTarget);
		g_graphicsEngine->EndGPUEvent();
	}
}