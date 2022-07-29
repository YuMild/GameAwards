#pragma once
namespace nsK2EngineLow {
	/// <summary>
	/// �X�N���[���X�y�[�X���t���N�V����
	/// </summary>
	class Ssr
	{
	public:
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="mainRenderTarget"></param>
		/// <param name="depthRenderTarget"></param>
		/// <param name="normalRenderTarget"></param>
		void OnInit
		(
			RenderTarget& mainRenderTarget,
			RenderTarget& depthRenderTarget,
			RenderTarget& normalRenderTarget
		);

		//�`��
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget);

		/// <summary>
		/// SSR��L���ɂ���
		/// </summary>
		void Enable()
		{
			m_isEnable = true;
		}

		/// <summary>
		/// SSR�𖳌��ɂ���
		/// </summary>
		void Disable()
		{
			m_isEnable = false;
		}
	private:
		struct SsrCb {
			Matrix mViewProjInv;				// �r���[�v���W�F�N�V�����s��̋t�s��B
			Matrix mViewProj;					// �r���[�v���W�F�N�V�����s��B
			Vector3 cameraPosInWorld;			// ���[���h���W�n�ł̃J�����̎��_�B
		};
		RenderTarget m_reflectionRt;			// �f�荞�݂����������ނ��߂̃����_�����O�^�[�Q�b�g�B
		RenderTarget m_finalRt;					// �ŏI�����X�v���C�g
		GaussianBlur m_blur;					// �u���[
		SsrCb m_ssrCb;							// GPU�ɓ]������f�[�^�B
		Sprite m_reflectionSprite;				// �f�荞�݉摜���쐬���邽�߂̃X�v���C�g
		Sprite m_finalSprite;					// �ŏI�����X�v���C�g�B
		bool m_isEnable;
	};
}