#pragma once

namespace nsK2EngineLow {

	//ディレクションライト。
	struct DirectionLight {
	private:
		Vector3 Direction;//ライトの⽅向。
		//HLSL側の定数バッファのfloat3型の変数は16の倍数のアドレスに配置されるため、C++側にはパディングを埋めておく。
		float pad;
		Vector3 Color;//ライトのカラー。
		float pad1;

	public:
		void SetDirection(Vector3& dir)
		{
			dir.Normalize();
			Direction = dir;
		}
		void SetColor(const Vector3& col)
		{
			Color = col;
		}
	};

	struct PointLight
	{
	private:
		Vector3 Position;
		float pad;
		Vector3 Color;
		float Range;
	public:
		void SetPosition(const Vector3& pos)
		{
			Position = pos;
		}
		void SetColor(const Vector3& col)
		{
			Color = col;
		}
		void SetRange(const float& rg)
		{
			Range = rg;
		}
		const Vector3 GetPosition()const 
		{
			return Position;
		}
	};
	struct SpotLight
	{
	private:
		Vector3 Position;			//位置
		float pad;					//パディング
		Vector3 Color;				//カラー
		float Range;				//影響範囲
		Vector3 Direction;			//射出方向
		float Angle;				//射出角度
	public:
		void SetPosition(const Vector3& pos)
		{
			Position = pos;
		}
		void SetColor(const Vector3& col)
		{
			Color = col;
		}
		void SetRange(const float& rg)
		{
			Range = rg;
		}
		void SetDirection(Vector3& dir)
		{
			dir.Normalize();
			Direction = dir;
		}
		void SetAngle(const float& ag)
		{
			Angle = ag;
		}

		void ApplyRotation(const Quaternion rot)
		{
			rot.Apply(Direction);
		}

		const Vector3& GetDirection()const
		{
			return Direction;
		}
		
	};

	struct Light
	{
		DirectionLight directionLight;
		PointLight pointLight;
		SpotLight spotLight;
		Vector3 ambientLight;
		float pad;
		Vector3 eyePos;
	};

		class SceneLight
		{



		public:
			SceneLight();

			Light& GetLight()
			{
				return m_light;
			}
			void SetAmbientLight(const Vector3& col)
			{
				m_light.ambientLight = col;
			}
			void SeteyePosition(const Vector3& pos)
			{
				m_light.eyePos = pos;
			}
			void SetPointLightPosition(const Vector3& pos)
			{
				m_light.pointLight.SetPosition(pos);
			}
			const Vector3 GetPointLightPosition()const 
			{
				return m_light.pointLight.GetPosition();
			}
			void ApplySpotLightRotation(const Quaternion& rot)
			{
				m_light.spotLight.ApplyRotation(rot);
			}
			const Vector3& GetSpotLightDirection()const
			{
				return m_light.spotLight.GetDirection();
			}


		private:
			Light m_light;
		};
		extern SceneLight g_sceneLight;
	}