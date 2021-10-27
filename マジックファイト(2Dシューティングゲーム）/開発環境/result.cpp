//=================================================================================================================
//
// リザルト画面の処理　〔result.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "title.h"
#include "player.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include "Score.h"
#include "sound.h"

//=================================================================================================================
// グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexClear[RESULT_CLEAR_MAX] = {};		// ゲームクリアした時の変数
LPDIRECT3DTEXTURE9 g_apTexGameOver[RESULT_OVER_MAX] = {};	// ゲームオーバーした時の変数
LPDIRECT3DTEXTURE9 g_pTexPush = NULL;						// ゲームオーバーした時の変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
bool g_bClear;							// クリアしたかどうか
bool g_bPushResult;						// プッシュが押されたか
int g_nCntPushResult;					// プッシュボタンの変数
int g_nCntEnterResult;					// プッシュボタンの変数
bool g_bEnterResult;					// プッシュが押されたか
float g_fResultMove;					// ロゴの変数
int g_nCntLogoMove;						// ロゴの変数



//*****************************************************************************************************************
// 初期化処理
//*****************************************************************************************************************
HRESULT InitResult(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 初期化
	g_nCntPushResult = 0;
	g_nCntEnterResult = 40;
	g_bPushResult = true;
	g_fResultMove = 18.0f;
	g_nCntLogoMove = 0;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RESULT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG002.jpg", &g_apTexClear[RESULT_CLEAR_BG]);				// ゲームクリア背景
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GAME CLEAR01.png", &g_apTexClear[RESULT_CLEAR_LOGO]);	// ゲームクリアロゴ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexClear[RESULT_CLEAR_PUSH]);	// ゲームクリアロゴ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG000.jpg", &g_apTexGameOver[RESULT_OVER_BG]);			// ゲームオーバーの背景
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GAME OVER00.png", &g_apTexGameOver[RESULT_OVER_LOGO]);	// ゲームオーバーのロゴ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexGameOver[RESULT_OVER_PUSH]);	// エンターロゴ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++, pVtx += 4)
	{
		// ゲームクリア、ゲームオーバーの背景設定
		if (nCntResult == RESULT_CLEAR_BG)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		// ゲームクリア、ゲームオーバーのロゴ設定
		else if (nCntResult == RESULT_CLEAR_LOGO)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(300.0f, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1000.0f, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1000.0f, 200.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		else if (nCntResult == RESULT_CLEAR_PUSH)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(900.0f, 700.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900.0f, 650.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1250.0f, 700.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1250.0f, 650.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		// rhwの設定（（（（（（（2Dでしか使わない））））））
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	// リザルト用BGM
	PlaySound(SOUND_LABEL_BGM003);

	return S_OK;
}

//*****************************************************************************************************************
// 終了処理
//*****************************************************************************************************************
void UninitResult(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++)
	{
		// テクスチャの開放
		if (g_apTexClear[nCntResult] != NULL)
		{
			g_apTexClear[nCntResult]->Release();
			g_apTexClear[nCntResult] = NULL;
		}

		// テクスチャの開放
		if (g_apTexGameOver[nCntResult] != NULL)
		{
			g_apTexGameOver[nCntResult]->Release();
			g_apTexGameOver[nCntResult] = NULL;
		}
	}

	//if (g_pTexPush != NULL)
	//{
	//	g_pTexPush->Release();
	//	g_pTexPush = NULL;
	//}

}
//*****************************************************************************************************************
//　更新処理
//*****************************************************************************************************************
void UpdateResult(void)
{
	VERTEX_2D *pVtx;

	// エンターキーが押された場合
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		StopSound(SOUND_LABEL_BGM003);	// サウンドを止める
		SetFade(FADE_OUT,MODE_TITLE);	// フェードさせ、タイトル画面に遷移する
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++, pVtx += 4)
	{
		if (nCntResult == RESULT_CLEAR_LOGO)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(1000.0f - g_fResultMove * g_nCntLogoMove, 400.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(1000.0f - g_fResultMove * g_nCntLogoMove, 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(1600.0f - g_fResultMove * g_nCntLogoMove, 400.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(1600.0f - g_fResultMove * g_nCntLogoMove, 200.0f, 0.0f);

			if (g_fResultMove * g_nCntLogoMove <= 650)
			{	
				g_nCntLogoMove++;
			}
		}

		// プッシュエンターの点滅処理
		if (nCntResult == RESULT_CLEAR_PUSH)
		{
			g_nCntPushResult++;

			if (g_nCntPushResult >= g_nCntEnterResult)
			{
				if (g_bPushResult == true)
				{
					// 頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					g_bPushResult = false;
				}

				else if (g_bPushResult == false)
				{
					// 頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPushResult = true;
				}
				g_nCntPushResult = 0;
			}
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

}

//*****************************************************************************************************************
// リザルトの描画処理
//*****************************************************************************************************************
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntResult = 0; nCntResult < MAX_RESULT; nCntResult++)
	{
		// ゲームクリアした時
		if (g_bClear == true)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTexClear[nCntResult]);
		}

		// ゲームオーバーの時
		if (g_bClear == false)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, g_apTexGameOver[nCntResult]);
		}

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntResult * 4, 2);
	}
}

//*****************************************************************************************************************
// リザルトの設定
//*****************************************************************************************************************
void SetResult(bool bClear)
{
	g_bClear = bClear;
}