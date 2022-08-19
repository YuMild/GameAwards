#include "k2EngineLowPreCompile.h"
#include "RenderingEngine.h"

namespace nsK2EngineLow
{
	RenderingEngine g_renderingEngine;
	void RenderingEngine::Render2DDraw(RenderContext& rc)
	{
		for (auto& renderObj : m_renderobject) {
			renderObj->OnRenderSprite2D(rc);
		}
		for (auto& renderObj : m_renderobject) {
			renderObj->OnRenderFont2D(rc);
		}
	}

	void RenderingEngine::ShadowMapDraw(RenderContext& rc)
	{
		Vector3 dir = { g_sceneLight.GetDirectionLightDirection().x,g_sceneLight.GetDirectionLightDirection().y,g_sceneLight.GetDirectionLightDirection().z };
		m_shadowMapRender.Render(rc, dir, m_renderobject);
	}
	void RenderingEngine::Execute(RenderContext& rc)
	{
		m_modelRenderCB.m_light = g_sceneLight.GetLight();
		m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
		//�Q�[���I�u�W�F�N�g�}�l�[�W���[�̕`�揈�����Ăяo���B
		
		ShadowMapDraw(rc);
		DrawModelAndDepth(rc);

		m_postEffect->Render(rc);

		Render2DDraw(rc);
		m_renderobject.clear();
	}
	void RenderingEngine::DrawModelAndDepth(RenderContext& rc)
	{
		//�����_�����O�^�[�Q�b�g��m_mainRenderTarget�ɕύX�B
		RenderTarget* renderTargets[] = { 
			&m_mainRenderTarget,
			&m_depthRenderTarget,
			&m_normalRenderTarget
		};

		rc.WaitUntilToPossibleSetRenderTargets(3, renderTargets);

		rc.SetRenderTargets(3, renderTargets);

		rc.ClearRenderTargetViews(3, renderTargets);

		//���f���̃h���[��g_engine->ExecuteRender();
		g_engine->ExecuteRender();

		rc.WaitUntilFinishDrawingToRenderTargets(3, renderTargets);
	}
	void RenderingEngine::Init()
	{
		m_postEffect = &g_postEffect;
		m_shadowMapRender.Init();
		m_modelRenderCB.m_light = g_sceneLight.GetLight();
		m_modelRenderCB.mlvp = GetLightCamera().GetViewProjectionMatrix();
		//�����_�����O�^�[�Q�b�g���쐬����B
		m_mainRenderTarget.Create(
			1600,												//�e�N�X�`���̕��B
			900,												//�e�N�X�`���̍����B
			1,													//Mipmap���x���B
			1,													//�e�N�X�`���z��̃T�C�Y�B
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_D32_FLOAT								//�f�v�X�X�e���V���o�b�t�@�̃t�H�[�}�b�g�B
		);
		m_depthRenderTarget.Create(
			1600,
			900,
			1,
			1,
			DXGI_FORMAT_R32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
		m_normalRenderTarget.Create(
			1600,
			900,
			1,
			1,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			DXGI_FORMAT_UNKNOWN
		);
	}
}