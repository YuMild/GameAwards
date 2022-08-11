#include "k2EngineLowPreCompile.h"
#include "PostEffect.h"

namespace nsK2EngineLow {

	PostEffect g_postEffect;

	void PostEffect::Init()
	{
		//�𑜓x�A�~�b�v�}�b�v���x��
		luminanceRenderTarget.Create(
			1600,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
			900,		//�𑜓x�̓��C�������_�����O�^�[�Q�b�g�Ɠ����B
			1,
			1,
			//�y���ځz�J���[�o�b�t�@�̃t�H�[�}�b�g��32bit���������_�ɂ��Ă���B
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT
		);

		m_monochromeRenderTarget.Create(
			1600,
			900,
			1,
			1,
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_D32_FLOAT
		);
	}

	void PostEffect::Render(RenderContext& rc)
	{
		RenderTarget* renderTarget[] = {
			&luminanceRenderTarget,
			&m_monochromeRenderTarget
		};

		rc.WaitUntilToPossibleSetRenderTargets(2,renderTarget);
		rc.SetRenderTargets(2,renderTarget);
		rc.ClearRenderTargetViews(2, renderTarget);
		rc.WaitUntilFinishDrawingToRenderTargets(2, renderTarget);
		rc.SetRenderTarget(
			g_graphicsEngine->GetCurrentFrameBuffuerRTV(),
			g_graphicsEngine->GetCurrentFrameBuffuerDSV()
		);

		SpriteInitData spriteInitData;
		spriteInitData.m_textures[0] = &g_renderingEngine.GetDepthRenderTarget().GetRenderTargetTexture();
		spriteInitData.m_width = 1000;
		spriteInitData.m_height = 600;
		spriteInitData.m_fxFilePath = "Assets/shader/sprite.fx";

		Sprite spsp;
		spsp.Init(spriteInitData);
		spsp.Draw(rc);

		//���m�N���X�v���C�g
		SpriteInitData monochromeSpriteInitData;
		monochromeSpriteInitData.m_textures[0] = &g_renderingEngine.GetmainRenderTarget().GetRenderTargetTexture();
		monochromeSpriteInitData.m_width = 1600;
		monochromeSpriteInitData.m_height = 900;
		monochromeSpriteInitData.m_fxFilePath = "Assets/shader/monochrome.fx";

		Sprite monochromeSprite;
		monochromeSprite.Init(monochromeSpriteInitData);
		monochromeSprite.Draw(rc);
	}
}