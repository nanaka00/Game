//=================================================================================================================
//
// 残機の処理　〔life.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "life.h"
#include "player.h"

//=================================================================================================================
//マクロ定義
//=================================================================================================================
#define MAX_LIFE (4)	//残りのライフ

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureLife = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;
bool bLife;	//
int g_nLife;

//*****************************************************************************************************************
// 残機の初期化処理
//*****************************************************************************************************************
HRESULT InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//初期ライフ
	g_nLife = 4;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL)))
	{
		return E_FAIL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Life00.png", &g_pTextureLife);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++, pVtx += 4)
	{
		//頂点座標の設定 (XYZ)
		pVtx[0].pos = D3DXVECTOR3(900.0f + (nCntLife * 70.0f), 100.0f, 0.0f);	//基準に()の中を＋する
		pVtx[1].pos = D3DXVECTOR3(900.0f + (nCntLife * 70.0f), 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1000.0f + (nCntLife *70.0f), 100.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000.0f + (nCntLife *70.0f), 10.0f, 0.0f);

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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	残機の終了処理
//*****************************************************************************************************************
void UninitLife(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}

	//テクスチャの開放
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}
}

//*****************************************************************************************************************
//	残機の更新処理
//*****************************************************************************************************************
void UpdateLife(void)
{
	PLAYER *pPlayer;

	pPlayer = GetPlayer();
	g_nLife = pPlayer->nLife / 10;
}

//*****************************************************************************************************************
//	残機の描画処理
//*****************************************************************************************************************
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLife = 0; nCntLife < g_nLife; nCntLife++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureLife);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLife * 4, 2);
	}
}
