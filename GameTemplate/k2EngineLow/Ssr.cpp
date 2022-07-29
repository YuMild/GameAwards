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
			//映り込み用
			SpriteInitData initData;
			initData.m_width = 1600;
			initData.m_height = 900;
			initData.m_fxFilePath = "Assets/shader/ssr.fx";
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
					0.0f, 0.0f, 0.0f, 0.0f
			};

			m_reflectionRt.Create(
				1600,
				900,
				1,
				1,
				mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN,
				clearColor
			);
		}
		m_blur.Init(&m_reflectionRt.GetRenderTargetTexture(), true);
		{
			// 最終合成用のスプライトを初期化する
			SpriteInitData initData;
			initData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
			initData.m_textures[1] = &m_blur.GetBokeTexture();

			// 解像度はmainRenderTargetの幅と高さ
			initData.m_width = mainRenderTarget.GetWidth();
			initData.m_height = mainRenderTarget.GetHeight();
			// 2D用のシェーダーを使用する
			initData.m_fxFilePath = "Assets/shader/ssr.fx";
			initData.m_vsEntryPointFunc = "VSMain";
			initData.m_psEntryPoinFunc = "PSFinal";

			initData.m_alphaBlendMode = AlphaBlendMode_None;
			initData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

			m_finalSprite.Init(initData);

			m_finalRt.Create(
				mainRenderTarget.GetWidth(),
				mainRenderTarget.GetHeight(),
				1,
				1,
				mainRenderTarget.GetColorBufferFormat(),
				DXGI_FORMAT_UNKNOWN
			);
		}
	};
	void Ssr::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		if (!m_isEnable) {
			return;
		}
		g_graphicsEngine->BeginGPUEvent("SSR");
		// まずは映り込みイメージを作成する。
		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_reflectionRt);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_reflectionRt);
		rc.ClearRenderTargetView(m_reflectionRt);

		m_ssrCb.cameraPosInWorld = g_camera3D->GetPosition();
		m_ssrCb.mViewProj = g_camera3D->GetViewProjectionMatrix();
		m_ssrCb.mViewProjInv.Inverse(m_ssrCb.mViewProj);

		// 描画
		m_reflectionSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_reflectionRt);

		// 映り込み画像をガウシアンブラーでぼかしてデノイズを行う。
		m_blur.ExecuteOnGPU(rc, 2.0f);

		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_finalRt);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_finalRt);
		// 映り込み画像とメインシーンを合成していく。
		m_finalSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_finalRt);
		g_graphicsEngine->EndGPUEvent();
	}
}