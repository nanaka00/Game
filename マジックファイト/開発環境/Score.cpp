//=================================================================================================================
//
// スコアの処理　〔Score.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "Score.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define MAX_SCORE (8)								//スコアの最大桁数
#define NUMBER_SIZE_X (40.0f)						//サイズの横幅
#define NUMBER_SIZE_Y (80.0f)						//サイズの縦幅


//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
int g_nScore;				//スコア

//*****************************************************************************************************************
// スコアの初期化処理
//*****************************************************************************************************************
HRESULT InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	g_nScore = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE LOGO.png", &g_pTextureScore);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++, pVtx += 4)
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
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	スコアの終了処理
//*****************************************************************************************************************
void UninitScore(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//テクスチャの開放
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//*****************************************************************************************************************
//	スコアの更新処理
//*****************************************************************************************************************
void UpdateScore(void)
{

}

//*****************************************************************************************************************
//	スコアの描画処理
//*****************************************************************************************************************
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureScore);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}
//*****************************************************************************************************************
//	スコア加算する
//*****************************************************************************************************************
void AddScore(int nValue)
{
	//変数宣言
	int aNumber[8];
	g_nScore += nValue;

	//構造体のポインター
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//スコアの格納
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++,pVtx += 4)
	{
		//桁を一つずつ格納
		aNumber[nCntScore] = (g_nScore / (int)powf(10.0f, (float)MAX_SCORE - (nCntScore + 1.0f)));

		//テクスチャ座標の設定(Nの順番）
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aNumber[nCntScore] * 0.1f), 1.0f / 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (aNumber[nCntScore] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntScore] * 0.1f), 1.0f /1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 10.0f + (aNumber[nCntScore] * 0.1f), 0.0);

	}
	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

//*****************************************************************************************************************
//	スコアのテクスチャ座標の更新
//*****************************************************************************************************************
void SetTextureScore(int nIdx,int nNumber)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx +=(nIdx * 4);

	//頂点情報の設定(Nの順番）
	pVtx[0].tex =  D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex =  D3DXVECTOR2(0.0f + (0.1f * nNumber), 0);
	pVtx[2].tex =  D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex =  D3DXVECTOR2(0.1f + (0.1f * nNumber), 0);

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

