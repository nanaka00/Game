//=================================================================================================================
//
// ポーズの処理　〔pause.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "pause.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"

//=================================================================================================================
//	マクロ定義
//=================================================================================================================
#define MAX_PAUSE (5)	// ポーズの種類

//=================================================================================================================
//	グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexPause[MAX_PAUSE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;
bool g_bPausse;
int g_nPointNow;
int g_nPoint;

//*****************************************************************************************************************
//	ポーズの初期化処理
//*****************************************************************************************************************
HRESULT InitPause(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// 初期化
	g_nPoint = 1;
	g_nPointNow = 1;
	g_bPausse = false;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_PAUSE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL)))
	{
		return E_FAIL;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\hawaiisbx.jpg", &g_apTexPause[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\CONTINUE00.png", &g_apTexPause[PAUSE_MENE_CONTINOE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\RETRY00.png", &g_apTexPause[PAUSE_MENE_RETRY]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\QUIT00.png", &g_apTexPause[PAUSE_MENE_QUIT]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\point000.png", &g_apTexPause[PAUSE_MENE_POINT]);


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++, pVtx += 4)
	{
		{
		if (nCntPause == 0)
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 100);
			pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 100);

		}

		if (nCntPause == 1)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(500, 350, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500, 300, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800, 350, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800, 300, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == 2)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(500, 450, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500, 400, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800, 450, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800, 400, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == 3)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(500, 550, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(500, 500, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(800, 550, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(800, 500, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntPause == 4)
		{		
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(450.0f, 350.0f + g_nPoint, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(450.0f, 300.0f + g_nPoint, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(500.0f, 350.0f + g_nPoint, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(500.0f, 300.0f + g_nPoint, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(0, 255, 225, 255);
			pVtx[1].col = D3DCOLOR_RGBA(0, 255, 225, 255);
			pVtx[2].col = D3DCOLOR_RGBA(0, 255, 225, 255);
			pVtx[3].col = D3DCOLOR_RGBA(0, 255, 225, 255);
		}
		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// rhwの設定（（（（（（（2Dでしか使わない）））））
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	ポーズの終了処理
//*****************************************************************************************************************
void UninitPause(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	for (int nCntPause = 0; nCntPause <MAX_PAUSE; nCntPause++)
	{
		// テクスチャの開放
		if (g_apTexPause[nCntPause] != NULL)
		{
			g_apTexPause[nCntPause]->Release();
			g_apTexPause[nCntPause] = NULL;
		}
	}
}

//*****************************************************************************************************************
//	ポーズの更新処理
//*****************************************************************************************************************
void UpdatePause(void)
{
	VERTEX_2D *pVtx;

	// Sキーを押した時(下に移動)
	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_nPoint += 100;
		g_nPointNow++;

		if (g_nPointNow > PAUSE_MENE_QUIT)		//QUITより下の時
		{
			g_nPointNow = PAUSE_MENE_CONTINOE;	
		}
		if (g_nPoint >= 300)
		{
			g_nPoint -= 300;
		}
	}



	// Wキーを押した時(上に移動)
	if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_nPoint -= 100;
		g_nPointNow--;
		if (g_nPointNow < PAUSE_MENE_CONTINOE)	// コンテニューより上の時
		{
			g_nPointNow = PAUSE_MENE_QUIT;
		}
		if (g_nPoint <= 0)
		{
			g_nPoint += 300;
		}
	}
	// エンターでポーズの決定
	if (GetKeyboardPress(DIK_RETURN) == true)
	{
		if (g_nPointNow == PAUSE_MENE_CONTINOE)
		{
			SetPause(false);
		}

		if (g_nPointNow == PAUSE_MENE_RETRY)
		{
			StopSound(SOUND_LABEL_BGM000);	// サウンドを止める 
			SetFade(FADE_OUT, MODE_GAME);	// ゲーム画面に飛ぶ＆フェードアウト
		}

		if (g_nPointNow == PAUSE_MENE_QUIT)
		{
			StopSound(SOUND_LABEL_BGM001);	// サウンドを止める
			SetFade(FADE_OUT, MODE_TITLE);	// フェードアウトをしてリザルト画面に飛ぶ
		}
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定 (XYZ)
	pVtx[16].pos = D3DXVECTOR3(450.0f, 350.0f + g_nPoint, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(450.0f, 300.0f + g_nPoint, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(500.0f, 350.0f + g_nPoint, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(500.0f, 300.0f + g_nPoint, 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

}

//*****************************************************************************************************************
//	ポーズの描画処理
//*****************************************************************************************************************
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPause = 0; nCntPause < MAX_PAUSE; nCntPause++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTexPause[nCntPause]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPause * 4, 2);
	}
}
