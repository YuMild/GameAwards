#pragma once
namespace nsK2EngineLow {
	class Bloom {
	public:
		//��4�����s
		void Init();

		//�ŏ�
		void InitSprite();
		//�P�x
		void InitLuminanceSprite();
		//�P�x�Ɋ|����u���[
		void InitBlurSprite();
		//�ŏI����
		void InitFinalSprite();

		void Render(RenderContext& rc, RenderTarget& rt);

		void Blur(RenderContext& rc);

		void Draw(RenderContext& rc);

		void LuminanceSpriteDraw(RenderContext& rc)
		{
			luminanceSprite.Draw(rc);
		}

		GaussianBlur gaussianBlur[4];
		Sprite luminanceSprite;
		Sprite copyToFrameBufferSprite;
		Sprite finalSprite;
	};
	extern Bloom g_bloom;
}