#pragma once
namespace nsK2EngineLow {
	class SerialNumberSpriteRender
	{
	public:
		/// <summary>
		/// 連番アニメーションの読み込み
		/// </summary>
		/// <param name="filePath">ファイルパス。_より前のやつ</param>
		/// <param name="w">横の長さ</param>
		/// <param name="h">縦の長さ</param>
		/// <param name="n">連番アニメーションの数。</param>
		/// <param name="alphaBlendMode">ブレンディングモード。</param>
		void Init(const char* filePath, const float w, const float h, const int n, AlphaBlendMode alphaBlendMode);

		void Update();

		/// <summary>
		/// 乗算カラーを設定。
		/// </summary>
		/// <param name="mulColor">乗算カラー。</param>
		void SetMulColor(const Vector4& mulColor)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetMulColor(mulColor);
			}
		}

		/// <summary>
		/// ピボットを設定。
		/// </summary>
		/// <param name="pivot">ピボット。</param>
		void SetPivot(const Vector2& pivot)
		{
			m_pivot = pivot;
		}
		/// <summary>
		/// 回転を設定。
		/// </summary>
		/// <param name="rot">回転。</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}


		/// <summary>
		/// 画像を描画する割合。
		/// </summary>
		/// <param name="x">描画する割合。1.0fが最大。</param>
		void SetLimitedX(const float x)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetLimitedX(x);
			}
			
		}
		void SetLimitedY(const float y)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetLimitedY(y);
			}
		}

		/// <summary>
		/// 原点を設定。原点を元として引数の分だけ画像を生成する。
		/// Left 0.5だと左から五割だけ画像が描写される。
		/// </summary>
		/// <param name="isLeft">原点。</param>
		void SetIsDisplayRestrictionLeftSide(const bool isLeft)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetIsDisplayRestrictionLeftSide(isLeft);
			}
		}
		void SetIsDisplayRestrictionRightSide(const bool isRight)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetIsDisplayRestrictionRightSide(isRight);
			}
		}

		void SetIsDisplayRestrictionUpSide(const bool isUp)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetIsDisplayRestrictionUpSide(isUp);
			}
		}
		void SetIsDisplayRestrictionDownSide(const bool isDown)
		{
			int spritenumber = m_spriteRenders.size();
			for (int i = 0; i < spritenumber; i++)
			{
				m_spriteRenders[i]->SetIsDisplayRestrictionDownSide(isDown);
			}
		}


	private:
		std::vector<std::unique_ptr<SpriteRender>> m_spriteRenders;
		Vector3			m_position = Vector3::Zero;				//座標。
		Quaternion		m_rotation = Quaternion::Identity;		//回転。
		Vector3			m_scale = Vector3::One;					//大きさ。
		Vector2			m_pivot = Sprite::DEFAULT_PIVOT;		//ピボット。
		int m_number;
	};

};