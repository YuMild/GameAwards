#pragma once
#include "SceneLight.h"
#include "ShadowMapRender.h"
#include "PostEffect.h"

namespace nsK2EngineLow
{
	struct ModelRenderCB
	{
	public:
		Light m_light;          // ライト
		Matrix mlvp; // ライトビュープロジェクション行列。
		Vector3 PlayerPosition = { 0.0f,0.0f,0.0f };
		Matrix mlvp;			// ライトビュープロジェクション行列。
		float DitheringLength=250.0f;
		float red;
	};
	class RenderingEngine :public Noncopyable
	{
	public:
		void Init();
		void AddRenderObject(IRenderer* renderobj)
		{
			m_renderobject.push_back(renderobj);
		}

		void Render2DDraw(RenderContext& rc);


		void SetPlayerPosition(Vector3 pos)
		{
			m_modelRenderCB.PlayerPosition = pos;
		}

		void SetRed(float n)
		{
			m_modelRenderCB.red = n;
		}
		const float GetRed()const
		{
			return m_modelRenderCB.red;
		}

		void ShadowMapDraw(RenderContext& rc);

		void Execute(RenderContext& rc);

		Texture& GetShadowMap()
		{
			return m_shadowMapRender.GetShadowMap();
		}
		Camera& GetLightCamera()
		{
			return m_shadowMapRender.GetLightCamera();
		}
		ModelRenderCB& GetModelRenderCB()
		{
			return m_modelRenderCB;
		}
		RenderTarget& GetDepthRenderTarget()
		{
			return m_depthRenderTarget;
		}
	private:
		std::vector<IRenderer*> m_renderobject;
		ShadowMapRender m_shadowMapRender;
		PostEffect* m_postEffect = &g_postEffect;
		ModelRenderCB m_modelRenderCB;
		RenderTarget m_mainRenderTarget;
		RenderTarget m_depthRenderTarget;
	};
	
	extern RenderingEngine g_renderingEngine;
}
