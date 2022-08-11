#pragma once
namespace nsK2EngineLow {
	class PostEffect
	{
	public:
		void Init();

		void Render(RenderContext& rc);
		
		RenderTarget luminanceRenderTarget;
		RenderTarget m_monochromeRenderTarget;
	};

	extern PostEffect g_postEffect;
}
