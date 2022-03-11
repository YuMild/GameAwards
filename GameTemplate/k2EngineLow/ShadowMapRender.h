#pragma once
namespace nsK2EngineLow {
	class ShadowMapRender
	{
	public:
		void Init();

		void Render(RenderContext& rc, Vector3& ligDirection);


		void AddShadowModel(Model& md)
		{
			m_Shadowmodels.push_back(&md);
		}


	private:
		RenderTarget shadowMap;
		std::vector<Model*> m_Shadowmodels;
	};

}