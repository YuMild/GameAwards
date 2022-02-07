#pragma once
namespace nsK2EngineLow {
	class SpriteRender
	{
	public:
		/// <summary>
		/// 初期化。
		/// </summary>
		/// <param name="filePath">ファイルパス。</param>
		/// <param name="w">画像の横幅。</param>
		/// <param name="h">画像の縦幅。</param>
		/// <param name="alphaBlendMode">デフォルトは半透明合成。</param>
		void Init(const char* filePath, const float w, const float h, AlphaBlendMode alphaBlendMode = AlphaBlendMode_Trans);

		void Draw(RenderContext& rc);








	private:
		Sprite			m_sprite;								//スプライト。
		Vector3			m_position = Vector3::Zero;				//座標。
		Quaternion		m_rotation = Quaternion::Identity;		//回転。
		Vector3			m_scale = Vector3::One;					//大きさ。
		Vector2			m_pivot = Sprite::DEFAULT_PIVOT;		//ピボット。
	};

}
