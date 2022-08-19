#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// スクリーンスペースリフレクション
	/// </summary>
	class Ssr
	{
	public:
		void OnInit
		(
			RenderTarget& mainRenderTarget,
			RenderTarget& depthRenderTarget,
			RenderTarget& normalRenderTarget
		);

		//描画
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// SSRを有効にする
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}

		/// <summary>
		/// SSRを無効にする
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
		}

	private:
		struct SsrCb {
			Matrix mViewProjInv;				// ビュープロジェクション行列の逆行列。
			Matrix mViewProj;					// ビュープロジェクション行列。
			Vector3 cameraPosInWorld;			// ワールド座標系でのカメラの視点。
		};
		RenderTarget m_reflectionRenderTarget;	// 映り込みをを書きこむためのレンダリングターゲット。
		RenderTarget m_finalRenderTarget;		// 最終合成スプライト
		GaussianBlur m_blur;					// ブラー
		SsrCb m_ssrCb;							// GPUに転送するデータ。
		Sprite m_reflectionSprite;				// 映り込み画像を作成するためのスプライト
		Sprite m_finalSprite;					// 最終合成スプライト。
		bool m_isEnable;
	};
}