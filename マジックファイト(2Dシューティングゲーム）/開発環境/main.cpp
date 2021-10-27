//=================================================================================================================
//
// 2Dゲームの処理　〔main.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "main.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "Score.h"
#include "sound.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "light.h"
#include "pause.h"
#include "rule.h"
#include "life.h"
#include "ranking.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define ID_BUTTON000	(101)		//ボタン000のID
#define ID_EDIT000		(111)		//エディットのID
#define ID_TIMER		(121)		//タイマーのID
#define TIMER_INTERVAL	(1000/60)	//タイマー発生間隔
#define WINDOW_POS_X    (500)		//ウィンドウの左上X座標
#define WINDOW_POS_Y    (100)		//ウィンドウの左上Y座標

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//=================================================================================================================
//　グローバル変数
//=================================================================================================================
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;				//フォントへのポインタ
int g_nCountFPS;						//FPSカウンタ

MODE g_mode = MODE_TITLE;				//モードの種類

//*****************************************************************************************************************
//	メイン関数
//*****************************************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//変数宣言
	RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };
	WNDCLASSEX wcex = 

	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL,IDI_APPLICATION),
		LoadCursor(NULL,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		"ファイル",
		LoadIcon(NULL,IDI_APPLICATION)
	};
	HWND hWnd;					//ウィンドウハンドル（識別子）
	MSG msg;					//メッセージを格納する
	DWORD dwExecLastTime;		//処理実行最終時刻
	DWORD dwFPSLastTime;		//FPS計測最終時刻
	DWORD dwCurrentTime;		//現在時刻
	DWORD dwFameCount;			//フレームカウント

	dwExecLastTime =
	dwFPSLastTime =
	dwCurrentTime = timeGetTime();
	dwFameCount = 0;

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//ウィンドウの大きさを調整する
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//ウィンドウの作成
	hWnd = CreateWindowEx(
		0,
		"ファイル",	//ウィンドウクラスの名前
		"MAGIC FIGHT",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL);


	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))	//falseだとフルスクリーン
	{
		return -1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{	//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{	//0.5秒経過
				g_nCountFPS = (dwFameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime; //最終時刻の保存
				dwFameCount = 0;
			}


			if ((dwCurrentTime - dwExecLastTime)>(1000/60))
			{
				//DirectXの処理
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update();
				//描画処理
				Draw();

				dwFameCount++;
			}
		}
	}
	//終了処理
	Uninit();

	//ウィンドウクラスの登録解除
	UnregisterClass(
		"ファイル",
		wcex.hInstance);

	return (int)msg.wParam;

}

//*****************************************************************************************************************
//ウィンドウプロシージャ
//*****************************************************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//変数宣言
	int nID;
	const RECT rect = { 0,0,SCREEN_WIDTH ,SCREEN_HEIGHT };


	switch (uMsg)
	{
		
	case WM_CLOSE:	//×ボタンが押された場合
		nID = MessageBox(NULL, "終了しますか？", "注意", MB_YESNO | MB_ICONSTOP);
		if (nID == IDYES)
		{
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_DESTROY:				//ウィンドウの破棄
		PostQuitMessage(0);			//WN_QUIT メッセージを返す
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				//ESCAPEキーが押されたとき
			DestroyWindow(hWnd);
			break;
		}
		break;
	default:
		
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
	
//*****************************************************************************************************************
//	初期化処理
//*****************************************************************************************************************
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//ディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//ディスプレイのプレゼンテーションパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));						// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;					// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;					// カラーモードの指定
	d3dpp.BackBufferCount = 1;								// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;			// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil = TRUE;				// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;			// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;							// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;				// リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;				// インターバル


	//Direct3Dデバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hWnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPU内で行う
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, 
			hWnd, 
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行う
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd, 
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &g_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				//カリングの設定
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				//αブレンドの設定
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ソース（描画元）
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//デスティネーションの合成方法の設定

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//縮小時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//拡大時　補間
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//U値　繰り返し
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTADDRESS_WRAP);	//V値　繰り返し

	//テクスチャステージステートの設定 (α値の合成）
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//初期化処理
	InitKeyboard(hInstance,hWnd);

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//サウンドの初期化処理
	InitSound(hWnd);

	//モードの設定
	SetMode(g_mode);
	
	//フェードの初期化処理
	InitFade(g_mode);

	return S_OK;
}

//*****************************************************************************************************************
//　終了処理
//*****************************************************************************************************************
void Uninit(void)
{
	//キーボードの	終了処理
	UninitKeyboard();

	//フェードの終了処理
	UninitFade();

	//画面遷移の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_RULE:
		UninitRule();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}
	//サウンドの終了処理
	UninitSound();

	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3Dデバイスの解放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの解放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL; 
	}
}
//*****************************************************************************************************************
//更新処理
//*****************************************************************************************************************
void Update(void)
{
	//入力デバイスの更新処理
	UpdateKeyboard();
	
	//画面遷移の更新処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_RULE:
		UpdateRule();
		break;

	case MODE_GAME:
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}
	UpdateFade();

}

//*****************************************************************************************************************
//	FPSの処理
//*****************************************************************************************************************
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	wsprintf(&aStr[0], "FPS %d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//*****************************************************************************************************************
//	描画処理
//*****************************************************************************************************************
void Draw(void)
{
	//バックバッファ＆Zバッファのクリア（画面のクリア）
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(255, 255, 255, 0), 1.0f, 0);


	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//画面遷移
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_RULE:
			DrawRule();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		default:
			break;
		}
		
		DrawFade();			//フェード

		#ifdef _DEBUG
		DrawFPS();			//FPS処理
		#endif

		//描画の終了
		g_pD3DDevice->EndScene();
	} 
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//*****************************************************************************************************************
//	モードの設定
//*****************************************************************************************************************
void SetMode(MODE mode)
{
	//画面遷移の終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_RULE:
		UninitRule();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	default:
		break;
	}
	g_mode = mode;

	//画面遷移の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_RULE:
		InitRule();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	default:
		break;
	}
}

MODE GetMode(void)
{
	return g_mode;
}
