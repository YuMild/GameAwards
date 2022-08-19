#pragma once
namespace nsK2EngineLow {
	class Bloom {
	public:
		//下4つを実行
		void Init();

		//最初
		void InitSprite();
		//輝度
		void InitLuminanceSprite();
		//輝度に掛けるブラー
		void InitBlurSprite();
		//最終合成
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