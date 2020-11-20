//=================================================================================================================
//
// ルール画面の処理　〔rule.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "rule.h"
#include "fade.h"
#include "input.h"

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTexRule = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;

//*****************************************************************************************************************
// 初期化処理
//*****************************************************************************************************************
HRESULT InitRule(void)
{

	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial000.png", &g_pTexRule);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffRule->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
// 終了処理
//*****************************************************************************************************************
void UninitRule(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}

	//テクスチャの開放
	if (g_pTexRule != NULL)
	{
		g_pTexRule->Release();
		g_pTexRule = NULL;
	}
}

//*****************************************************************************************************************
//　更新処理
//*****************************************************************************************************************
void UpdateRule(void)
{
	//エンターキーが押された場合
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_GAME);
	}
}
//********************************************************************** *******************************************
// リザルトの描画処理
//*****************************************************************************************************************
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexRule);
	
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}
