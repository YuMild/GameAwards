#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {


	ModelRender::ModelRender()
	{
		

	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Update()
	{
		
	
		if (m_animationClip != nullptr)
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
			
		}
		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime()* m_animationSpeed);
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_shadowmodel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}
	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);

		g_renderingEngine.AddRenderObject(this);
	}
	void ModelRender::Init(const char* filePath,
		bool shadowRecieve,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		ModelInitData initData;
		//シェーダーファイルのファイルパス。
		initData.m_fxFilePath = "Assets/shader/model.fx";


		//モデルの定数バッファ用の情報をモデルの初期化情報として渡す。
		initData.m_expandConstantBuffer = &g_renderingEngine.GetModelRenderCB();
		initData.m_expandConstantBufferSize = sizeof(g_renderingEngine.GetModelRenderCB());
		if (animationClips == nullptr)
		{
			//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
			initData.m_vsEntryPointFunc = "VSMain";
		}
		else
		{
			//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			InitSkeleton(filePath);
			//スケルトンを指定する。
			initData.m_skeleton = &m_skeleton;
			InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		}

		if (shadowRecieve) {
			initData.m_psEntryPointFunc = "PSMainShadowReciever";
			m_isShadowCaster = false;
		}
		else
		{
			m_isShadowCaster = true;
		}
		//シャドウマップを拡張SRVに設定する。
		initData.m_expandShaderResoruceView[0] = &g_renderingEngine.GetShadowMap();
		initData.m_tkmFilePath = filePath;
		
		m_enFbxUpAxis = enModelUpAxis;
		initData.m_modelUpAxis = m_enFbxUpAxis;
		m_model.Init(initData);
		InitShadowModel(filePath, m_enFbxUpAxis);

	}
	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}
	void ModelRender::InitAnimation(
		AnimationClip* animationClip,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		m_animationClip = animationClip;
		m_numAnimationClips = numAnimationClips;
		m_animation.Init
		(	m_skeleton,
			m_animationClip,
			m_numAnimationClips
		);

	}

	void ModelRender::InitShadowModel(const char* tkmFilePath,EnModelUpAxis modelUpAxis)
	{
		ModelInitData ShadowModelInitData;

		// シャドウマップ描画用のシェーダーを指定する
		ShadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
		ShadowModelInitData.m_tkmFilePath = tkmFilePath;
		if (m_animationClip != nullptr) {
			//スケルトンを指定する。
			ShadowModelInitData.m_skeleton = &m_skeleton;
			//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
			ShadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		}
		else
		{
			ShadowModelInitData.m_vsSkinEntryPointFunc = "VSMain";
		}
		ShadowModelInitData.m_colorBufferFormat[0]=DXGI_FORMAT_R32_FLOAT,
		m_shadowmodel.Init(ShadowModelInitData);
		

	}
	void ModelRender::OnRenderShadowMap(RenderContext& rc, const Matrix& lvpMatrix)
	{
		if (m_isShadowCaster)
		{
			m_shadowmodel.Draw(
				rc,
				g_matIdentity,
				lvpMatrix);

		}
	}
}