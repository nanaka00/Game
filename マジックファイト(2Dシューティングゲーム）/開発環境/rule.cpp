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
// グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexRule[MAX_RULE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRule = NULL;

bool g_bPushRule;			// プッシュが押されたか
int g_nCntPushRule;			// プッシュボタンの変数
int g_nCntEnterRule;		// プッシュボタンの変数
bool g_bEnterRule;			// プッシュが押されたか

//*****************************************************************************************************************
// 初期化処理
//*****************************************************************************************************************
HRESULT InitRule(void)
{
	// 変数
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	 
	// デバイスの取得
	pDevice = GetDevice();

	// 初期化
	g_nCntPushRule = 0;
	g_nCntEnterRule = 40;
	g_bPushRule = true;
	g_bEnterRule = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial000.png", &g_apTexRule[RULE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexRule[RULE_PUSH]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_RULE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRule,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++, pVtx += 4)
	{
		if (nCntRule == RULE_BG)
		{

			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}

		else if (nCntRule == RULE_PUSH)
		{

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
	g_pVtxBuffRule->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
// 終了処理
//*****************************************************************************************************************
void UninitRule(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffRule != NULL)
	{
		g_pVtxBuffRule->Release();
		g_pVtxBuffRule = NULL;
	}

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++)
	{
		// テクスチャの開放
		if (g_apTexRule[nCntRule] != NULL)
		{
			g_apTexRule[nCntRule]->Release();
			g_apTexRule[nCntRule] = NULL;
		}
	}
}

//*****************************************************************************************************************
//　更新処理
//*****************************************************************************************************************
void UpdateRule(void)
{
	VERTEX_2D *pVtx;

	// エンターキーが押された場合
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(FADE_OUT, MODE_GAME);	// フェードし、ゲーム画面に遷移する
		g_bEnterRule = true;			// エンターを押した判定にする
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRule->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++, pVtx += 4)
	{
		// プッシュエンターの点滅処理
		if (nCntRule == RULE_PUSH)
		{
			g_nCntPushRule++;

			if (g_nCntPushRule >= g_nCntEnterRule)
			{
				if (g_bPushRule == true)
				{
					// 頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

					g_bPushRule = false;
				}

				else if (g_bPushRule == false)
				{
					// 頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPushRule = true;
				}
				g_nCntPushRule = 0;
			}

			// エンター押されたら
			if (g_bEnterRule == true)
			{
				g_nCntEnterRule = 12;
			}
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffRule->Unlock();
}
//*****************************************************************************************************************
// リザルトの描画処理
//*****************************************************************************************************************
void DrawRule(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffRule, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRule = 0; nCntRule < MAX_RULE; nCntRule++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTexRule[nCntRule]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntRule * 4, 2);
	}
}
