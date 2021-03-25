//=================================================================================================================
//
// タイマーの処理　〔time.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "time.h"
#include "result.h"
#include "fade.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define MAX_TIME (3)

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureTime = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufTime = NULL;
int g_nTime;
int g_nCntTime;

//*****************************************************************************************************************
// タイマーの初期化処理
//*****************************************************************************************************************
HRESULT InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	g_nCntTime = 130;
	g_nTime = 44;
	
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBufTime,
		NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE LOGO.png", &g_pTextureTime);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, pVtx += 4)
	{

		//頂点座標の設定 (XYZ)（Updateをしないものは、ここで初期位置を決める）
		pVtx[0].pos = D3DXVECTOR3(500.0f + (nCntTime * 55.0f), 100.0f, 0.0f);	//基準に()の中を＋する
		pVtx[1].pos = D3DXVECTOR3(500.0f + (nCntTime * 55.0f), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(600.0f + (nCntTime * 55.0f), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(600.0f + (nCntTime * 55.0f), 10.0f, 0.0f);

		//rhwの設定（（（（（（（2Dでしか使わない））））））
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(255, 10, 200, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 10, 200, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 10, 200, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 10, 200, 255);

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	}
	//頂点バッファをアンロックする
	g_pVtxBufTime->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	タイマーの終了処理
//*****************************************************************************************************************
void UninitTime(void)
{
	//頂点バッファの開放
	if (g_pVtxBufTime != NULL)
	{
		g_pVtxBufTime->Release();
		g_pVtxBufTime = NULL;
	}

	//テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//*****************************************************************************************************************
//	タイマーの更新処理
//*****************************************************************************************************************
void UpdateTime(void)
{
	VERTEX_2D *pVtx;
	int aNumber[8];

	if (g_nTime != 0)
	{
		g_nCntTime -= 1;
	}
	if (g_nCntTime == 0)
	{
		g_nTime -= 1;
		g_nCntTime = 60;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufTime->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++, pVtx += 4)
	{
		aNumber[nCntTime] = (g_nTime / (int)powf(10.0f, (float)(MAX_TIME - (nCntTime + 1))));

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntTime] * 0.1f), 0.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBufTime->Unlock();

	if (g_nTime == 0)
	{
		SetResult(true);
		SetFade(FADE_OUT, MODE_RESULT);
	}
}

//*****************************************************************************************************************
//	タイマーの描画処理
//*****************************************************************************************************************
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBufTime, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTime);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
	}
}
//*****************************************************************************************************************
//	タイマーのテクスチャ座標の更新
//*****************************************************************************************************************
void SetTextureTime(int nIdx, int nNumber)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBufTime->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	//頂点情報の設定(Nの順番）
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 0);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 0);

	//頂点バッファをアンロックする
	g_pVtxBufTime->Unlock();
}

