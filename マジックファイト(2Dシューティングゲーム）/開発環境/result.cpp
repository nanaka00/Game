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
//	列挙型 (複数の変数に一連の整数値を付ける必要がある場合に使う）
//=================================================================================================================
//敵の種類
typedef enum
{
	RESULT_000 = 0,	//新米魔法使いエンド
	RESULT_001,		//にわか魔法使いエンド
	RESULT_002,		//一人前の魔法使いエンド
	RESULT_003,		//永久不滅の魔法使いエンド
	RESULT_004,		//ゲームオーバーエンド
	RESULT_MAX		//種類の最大値
}RESULT;

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTexResult = NULL;
LPDIRECT3DTEXTURE9 g_pTexGameOver = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;
bool g_bClear;	//

//*****************************************************************************************************************
// 初期化処理
//*****************************************************************************************************************
HRESULT InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM003);

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG006.png", &g_pTexResult);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG004.png", &g_pTexGameOver);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResult,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点座標の設定 (XYZ)
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	//rhwの設定（（（（（（（2Dでしか使わない））））））
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//頂点バッファをアンロックする
	g_pVtxBuffResult->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
// 終了処理
//*****************************************************************************************************************
void UninitResult(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//テクスチャの開放
	if (g_pTexGameOver != NULL)
	{
		g_pTexGameOver->Release();
		g_pTexGameOver = NULL;
	}
	//テクスチャの開放
	if (g_pTexResult != NULL)
	{
		g_pTexResult->Release();
		g_pTexResult = NULL;
	}
}

//*****************************************************************************************************************
//　更新処理
//*****************************************************************************************************************
void UpdateResult(void)
{
	//エンターキーが押された場合
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		StopSound(SOUND_LABEL_BGM003);
		SetFade(FADE_OUT,MODE_TITLE); 
	}
}
//********************************************************************** *******************************************
// リザルトの描画処理
//*****************************************************************************************************************
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ゲームクリアした時
	if (g_bClear == true)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexResult);
	}
	else if(g_bClear == false)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexGameOver);
	}
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
}
//*****************************************************************************************************************
// リザルトの設定
//*****************************************************************************************************************
void SetResult(bool bClear)
{
	g_bClear = bClear;
}