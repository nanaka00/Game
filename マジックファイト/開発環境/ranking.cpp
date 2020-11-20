//=================================================================================================================
//
// ランキングの処理　〔ranking.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "ranking.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define MAX_RANKING (8)								//スコアの最大桁数


//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;

//*****************************************************************************************************************
// スコアの初期化処理
//*****************************************************************************************************************
HRESULT InitRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RANKING,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRanking,
		NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE LOGO.png", &g_pTextureRanking);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++, pVtx += 4)
	{

		//頂点座標の設定 (XYZ)（Updateをしないものは、ここで初期位置を決める）
		pVtx[0].pos = D3DXVECTOR3(40.0f + (nCntScore * 35.0f), 100.0f, 0.0f);	//基準に()の中を＋する
		pVtx[1].pos = D3DXVECTOR3(40.0f + (nCntScore * 35.0f), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(100.0f + (nCntScore * 35.0f), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(100.0f + (nCntScore * 35.0f), 10.0f, 0.0f);

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

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

	}
	//頂点バッファをアンロックする
	g_pVtxBuffRanking->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	スコアの終了処理
//*****************************************************************************************************************
void UninitRanking(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	//テクスチャの開放
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
}

//*****************************************************************************************************************
//	スコアの更新処理
//*****************************************************************************************************************
void UpdateRanking(void)
{

}

//*****************************************************************************************************************
//	スコアの描画処理
//*****************************************************************************************************************
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < MAX_RANKING; nCntScore++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureRanking);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//*****************************************************************************************************************
//	スコアの描画処理
//*****************************************************************************************************************
void OldScore(void)
{
	
}

