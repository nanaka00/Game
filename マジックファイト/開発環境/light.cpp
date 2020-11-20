//=================================================================================================================
//
// ライトの処理　〔main.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "light.h"
#include "input.h"
#include "player.h"

//=================================================================================================================
//	マクロ定義
//=================================================================================================================
#define LIGHT_X (1300)		//ライトテクスチャのXの値
#define LIGHT_Y (800)		//ライトテクスチャのYの値
#define LIGHT_SPEED (6.5f)
#define GAUGE_X_1	(950.0f)
#define GAUGE_X_2	(1250.0f)
#define GAUGE_Y_1	(700.0f)
#define GAUGE_Y_2	(670.0f)

#define MAX_LIGHT (3)

//=================================================================================================================
//	グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexLight[MAX_LIGHT] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLight = NULL;
PLAYER g_posLight;		//ライトの位置
float g_Light;			//ライトの変数
bool g_bLight;			//ライトが使われているか

//*****************************************************************************************************************
//	ライトの初期化処理
//*****************************************************************************************************************
HRESULT InitLight(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//初期化
	g_Light = 0;
	g_bLight = true;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\light.png", &g_apTexLight[LIGHT_LIGHT]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Gauge00.png", &g_apTexLight[LIGHT_GAUGE]);

	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\GaugeW.png", &g_apTexLight[LIGHT_GAUGEW]);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_LIGHT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLight,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLight->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++, pVtx += 4)
	{
		if (nCntLight == LIGHT_LIGHT)
		{
			//頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT * 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 2, -SCREEN_HEIGHT, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 245);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 245);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 245);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 245);
		}

		if (nCntLight == LIGHT_GAUGE)
		{
			//頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_1, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_1, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_2, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		if (nCntLight == LIGHT_GAUGEW)
		{
			//頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_1, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_1, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(GAUGE_X_2, GAUGE_Y_2, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		//rhwの設定（（（（（（（2Dでしか使わない））））））
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}
	//頂点バッファをアンロックする
	g_pVtxBuffLight->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	ライトの終了処理
//*****************************************************************************************************************
void UninitLight(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffLight != NULL)
	{
		g_pVtxBuffLight->Release();
		g_pVtxBuffLight = NULL;
	}

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//テクスチャの開放
		if (g_apTexLight[nCntLight] != NULL)
		{
			g_apTexLight[nCntLight]->Release();
			g_apTexLight[nCntLight] = NULL;
		}
	}
}

//*****************************************************************************************************************
//	ライトの更新処理
//*****************************************************************************************************************
void UpdateLight(void)
{
	//変数宣言
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;

	//プレイヤーと一緒に動かす
	pPlayer = GetPlayer();

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLight->Lock(0, 0, (void**)&pVtx, 0);
	
	//頂点座標の設定 (XYZ)
	pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x -SCREEN_WIDTH, pPlayer->pos.y + SCREEN_HEIGHT * 1.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x -SCREEN_WIDTH, pPlayer->pos.y - SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH * 1.0f, pPlayer->pos.y + SCREEN_HEIGHT * 1.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH * 1.0f, pPlayer->pos.y - SCREEN_HEIGHT, 0.0f);

	//***************************
	//ライトのゲージの処理
	//***************************
	//変数宣言
	g_Light -= 1.5f;	//更新するたびゲージを減らす
	
	//0より大きくなったらライトが使える
	if (g_Light <= 0)
	{
		g_Light = 0;
		g_bLight = true;
	}

	if (g_bLight == true)
	{
		//ライトが大きくなる
		if (GetKeyboardPress(DIK_L) == true)
		{
			g_Light += 3.5f;

			//頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(pPlayer->pos.x - SCREEN_WIDTH - LIGHT_X, pPlayer->pos.y + SCREEN_HEIGHT + LIGHT_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(pPlayer->pos.x - SCREEN_WIDTH - LIGHT_X, pPlayer->pos.y - SCREEN_HEIGHT - LIGHT_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH + LIGHT_X, pPlayer->pos.y + SCREEN_HEIGHT + LIGHT_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(pPlayer->pos.x + SCREEN_WIDTH + LIGHT_X, pPlayer->pos.y - SCREEN_HEIGHT - LIGHT_Y, 0.0f);

			//300より大きくなったらライトを使えなくなる
			if (g_Light >= 300)
			{
				g_bLight = false;

			}
		}
	}
	//頂点座標の設定 (XYZ)
	pVtx[4].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_1, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(GAUGE_X_1, GAUGE_Y_2, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(GAUGE_X_2 - g_Light, GAUGE_Y_1, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(GAUGE_X_2 - g_Light, GAUGE_Y_2, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffLight->Unlock();
}

//*****************************************************************************************************************
//	ライトの描画処理
//*****************************************************************************************************************
void DrawLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffLight, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexLight[nCntLight]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntLight * 4, 2);
	}
}


