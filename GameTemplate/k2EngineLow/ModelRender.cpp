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
		
		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime());
		if (m_animationClip != nullptr)
		{
			m_skeleton.Update(m_model.GetWorldMatrix());
		}
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}
	void ModelRender::Draw(RenderContext& rc)
	{
		m_model.Draw(rc);
	}
	void ModelRender::Init(const char* filePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		ModelInitData initData;
		//シェーダーファイルのファイルパス。
		initData.m_fxFilePath = "Assets/shader/model.fx";


		//ディレクションライトの情報を定数バッファとしてディスクリプタヒープに登録するために
		//モデルの初期化情報として渡す。
		initData.m_expandConstantBuffer = &g_sceneLight.GetLight();
		initData.m_expandConstantBufferSize = sizeof(g_sceneLight.GetLight());
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
		initData.m_tkmFilePath = filePath;
		


		m_enFbxUpAxis = enModelUpAxis;
		initData.m_modelUpAxis = m_enFbxUpAxis;
		m_model.Init(initData);

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

}