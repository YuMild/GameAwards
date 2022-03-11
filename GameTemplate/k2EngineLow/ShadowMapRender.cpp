#include "k2EngineLowPreCompile.h"
#include "ShadowMapRender.h"

namespace nsK2EngineLow {



	void ShadowMapRender::Init()
	{


        // シャドウマップ描画用のレンダリングターゲットを作成する
        float clearColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        RenderTarget shadowMap;
        shadowMap.Create(
            1024,
            1024,
            1,
            1,
            DXGI_FORMAT_R8G8B8A8_UNORM,
            DXGI_FORMAT_D32_FLOAT,
            clearColor
        );
	}

    void ShadowMapRender::Render(RenderContext& rc, Vector3& ligDirection)
    {
        // 影描画用のライトカメラを作成する
        Camera lightCamera;
        // カメラの位置を設定。これはライトの位置
        lightCamera.SetPosition(0, 500, 0);

        // カメラの注視点を設定。これがライトが照らしている場所
        lightCamera.SetTarget(0, 0, 0);

        // 上方向を設定。今回はライトが真下を向いているので、X方向を上にしている
        lightCamera.SetUp(1, 0, 0);

        // ライトビュープロジェクション行列を計算している
        lightCamera.Update();

        rc.WaitUntilToPossibleSetRenderTarget(shadowMap);
        rc.SetRenderTargetAndViewport(shadowMap);
        rc.ClearRenderTargetView(shadowMap);

        for (auto& model : m_Shadowmodels)
        {
            model->Draw(
                rc,
                g_matIdentity,
                lightCamera.GetProjectionMatrix()
            );
        }
        //描画が終わったのでクリア。
        m_Shadowmodels.clear();
        // 書き込み完了待ち
        rc.WaitUntilFinishDrawingToRenderTarget(shadowMap);
       

       
    }














}