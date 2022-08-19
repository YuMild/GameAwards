#include "k2EngineLowPreCompile.h"
#include "Bloom.h"

namespace nsK2EngineLow {

	Bloom g_bloom;

	void Bloom::Init()
	{
		InitLuminanceSprite();
		InitBlurSprite();
		InitFinalSprite();
		InitSprite();
	}

	void Bloom::InitSprite()
	{
		SpriteInitData spriteInitData;
		spriteInitData.m_textures[0] = &g_renderingEngine.GetmainRenderTarget().GetRenderTargetTexture();
		spriteInitData.m_width = 1600;
		spriteInitData.m_height = 900;
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		copyToFrameBufferSprite.Init(spriteInitData);
	}

	void Bloom::InitLuminanceSprite()
	{
		SpriteInitData luminanceSpriteInitData;
		luminanceSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		luminanceSpriteInitData.m_vsEntryPointFunc = "VSMain";
		luminanceSpriteInitData.m_psEntryPoinFunc = "PSSamplingLuminance";
		luminanceSpriteInitData.m_width = 1600;
		luminanceSpriteInitData.m_height = 900;
		luminanceSpriteInitData.m_textures[0] = &g_renderingEngine.GetmainRenderTarget().GetRenderTargetTexture();
		luminanceSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		luminanceSprite.Init(luminanceSpriteInitData);
	}

	void Bloom::InitBlurSprite()
	{
		gaussianBlur[0].Init(&g_postEffect.luminanceRenderTarget.GetRenderTargetTexture());
		gaussianBlur[1].Init(&gaussianBlur[0].GetBokeTexture());
		gaussianBlur[2].Init(&gaussianBlur[1].GetBokeTexture());
		gaussianBlur[3].Init(&gaussianBlur[2].GetBokeTexture());
	}

	void Bloom::InitFinalSprite()
	{
		SpriteInitData finalSpriteInitData;
		//êÏê£éÆÉuÉãÅ[ÉÄ
		finalSpriteInitData.m_textures[0] = &gaussianBlur[0].GetBokeTexture();
		finalSpriteInitData.m_textures[1] = &gaussianBlur[1].GetBokeTexture();
		finalSpriteInitData.m_textures[2] = &gaussianBlur[2].GetBokeTexture();
		finalSpriteInitData.m_textures[3] = &gaussianBlur[3].GetBokeTexture();
		finalSpriteInitData.m_width = 1600;
		finalSpriteInitData.m_height = 900;
		finalSpriteInitData.m_fxFilePath = "Assets/shader/PostEffect.fx";
		finalSpriteInitData.m_psEntryPoinFunc = "PSBloomFinal";

		finalSpriteInitData.m_alphaBlendMode = AlphaBlendMode_Add;
		finalSpriteInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32G32B32A32_FLOAT;

		finalSprite.Init(finalSpriteInitData);
	}

	void Bloom::Draw(RenderContext& rc)
	{
		copyToFrameBufferSprite.Draw(rc);
	}

	void Bloom::Blur(RenderContext& rc)
	{
		gaussianBlur[0].ExecuteOnGPU(rc, 10);
		gaussianBlur[1].ExecuteOnGPU(rc, 10);
		gaussianBlur[2].ExecuteOnGPU(rc, 10);
		gaussianBlur[3].ExecuteOnGPU(rc, 10);
	}

	void Bloom::Render(RenderContext& rc,RenderTarget& rt)
	{
		rc.WaitUntilToPossibleSetRenderTarget(rt);
		rc.SetRenderTargetAndViewport(rt);
		finalSprite.Draw(rc);
		rc.WaitUntilFinishDrawingToRenderTarget(rt);
	}
}