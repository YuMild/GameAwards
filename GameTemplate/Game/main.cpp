#include "stdafx.h"
#include "system/system.h"

#include "First.h"

// K2EngineLowのグローバルアクセスポイント。
K2EngineLow* g_k2EngineLow = nullptr;

/// <summary>
/// メイン関数
/// </summary>
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	// ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));

	// k2EngineLowの初期化。
	g_k2EngineLow = new K2EngineLow();
	g_k2EngineLow->Init(g_hWnd, FRAME_BUFFER_W, FRAME_BUFFER_H);
	g_camera3D->SetPosition({ 0.0f, 100.0f, -200.0f });
	g_camera3D->SetTarget({ 0.0f, 50.0f, 0.0f });
	g_sceneLight.SeteyePosition(g_camera3D->GetPosition());

	NewGO<First>(0, "first");

	g_postEffect.Init();
	g_bloom.Init();
	//step-2 ポストエフェクト実行用のスプライトを初期化する。
	//スプライトの初期化オブジェクトを作成する。
	SpriteInitData spriteInitData;
	//【重要！！！】テクスチャはオフスクリーンレンダリングされた絵。
	spriteInitData.m_textures[0] = &g_postEffect.mainRenderTarget.GetRenderTargetTexture();
	//【重要！！！】全画面描画なのでスプライトのサイズはフレームバッファと同じにする。
	spriteInitData.m_width = 1600;
	spriteInitData.m_height = 900;
	//【重要！！！】モノクロ用のシェーダーを指定する。
	spriteInitData.m_fxFilePath = "Assets/shader/monochrome.fx";
	//初期化オブジェクトを使って、スプライトを初期化する。
	Sprite monochromeSprite;
	monochromeSprite.Init(spriteInitData);



	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		auto& renderContext = g_graphicsEngine->GetRenderContext();

		// フレームの開始時に呼び出す必要がある処理を実行
		g_k2EngineLow->BeginFrame();

		// ゲームオブジェクトマネージャーの更新処理を呼び出す。
		g_k2EngineLow->ExecuteUpdate();

		// ゲームオブジェクトマネージャーの描画処理を呼び出す。
		g_k2EngineLow->ExecuteRender();

		//TODO オフスクリーンレンダリングの処理
		g_postEffect.Render(renderContext);
		
		EffectEngine::GetInstance()->Draw();

		g_renderingEngine.FontRenderDraw(renderContext);

		//TODO spriteの描画。
		g_renderingEngine.SpriteRenderDraw(renderContext);

		// デバッグ描画処理を実行する。
		g_k2EngineLow->DebubDrawWorld();

		// フレームの終了時に呼び出す必要がある処理を実行。
		g_k2EngineLow->EndFrame();
	}
	delete g_k2EngineLow;

	return 0;
}