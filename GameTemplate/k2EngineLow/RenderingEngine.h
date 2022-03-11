#pragma once

namespace nsK2EngineLow
{
	class RenderingEngine //:public Noncopyable
	{
	public:
        /// <summary>
		/// 描画オブジェクトを追加。
		/// </summary>
		/// <param name="renderObject">スプライトレンダー</param>
        void AddSpriteRenderObject(SpriteRender* renderObject)
        {
            m_Spriterenders.push_back(renderObject);
        }

		void AddFontRenderObject(FontRender* renderObject)
		{
			m_Fontrenders.push_back(renderObject);
		}


		void SpriteRenderDraw(RenderContext& rc);

		void FontRenderDraw(RenderContext& rc);

		void AddShadowRenderModel(Model& md)
		{
			m_shadowMapRender.AddShadowModel(md);
		}
		
	private:
		std::vector<SpriteRender*>	m_Spriterenders;
		std::vector<FontRender*>	m_Fontrenders;
		ShadowMapRender m_shadowMapRender;
		
	};

	extern RenderingEngine g_renderingEngine;

}
