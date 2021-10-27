//=================================================================================================================
//
// タイトルの処理　〔title.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "title.h"
#include "input.h"
#include "player.h"
#include "fade.h"
#include "sound.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================

//=================================================================================================================
//　グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_apTexTitle[MAX_TITLE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;
int g_Title;
float g_TitleMove;		// タイトルロゴの変数
int g_CntMove;			// タイトルロゴの変数
float g_MiniMove;		// サブタイトルロゴの変数
int g_CntMiniMove;		// サブタイトルロゴの変数
bool g_bPush;			// プッシュが押されたか
int g_nCntPush;			// プッシュボタンの変数
int g_nCntEnter;		// プッシュボタンの変数
bool g_bEnter;			// プッシュが押されたか

//*****************************************************************************************************************
// タイトルの初期化処理
//*****************************************************************************************************************
HRESULT InitTitle(void)
{
	// 変数
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// 初期化
	g_TitleMove = 15.0f;		// タイトルロゴ
	g_CntMove = 0;			// タイトルロゴ
	g_MiniMove = 15.0f;		// サブタイトルロゴ
	g_CntMiniMove = 0;		// サブタイトルロゴ
	g_nCntPush = 0;			
	g_nCntEnter = 40;		
	g_bPush = true;
	g_bEnter = false;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_TITLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL)))
	{
		return E_FAIL;
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG002.jpg", &g_apTexTitle[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\chara.png", &g_apTexTitle[TITLE_LOGO]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cyara.png", &g_apTexTitle[TITLE_LOGO2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MAGICFIGHT　LOGO1.png", &g_apTexTitle[TITLE_TITLE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\MAGICFIGHT　LOGO.png", &g_apTexTitle[TITLE_MINI]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER01.png", &g_apTexTitle[TITLE_PUSH]);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_BG)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(100, 0, 100, 255);
			pVtx[1].col = D3DCOLOR_RGBA(100, 0, 100, 255);
			pVtx[2].col = D3DCOLOR_RGBA(100, 0, 100, 255);
			pVtx[3].col = D3DCOLOR_RGBA(100, 0, 100, 255);
		}

		else if (nCntTitle == TITLE_LOGO)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(900.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(900.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH + 500.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH + 500.0f, 0.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		}
		else if (nCntTitle == TITLE_LOGO2)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(-400.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(-400.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(350.0f, SCREEN_HEIGHT + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(350.0f, 0.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);
		}

		else if (nCntTitle == TITLE_TITLE)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 40, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 140, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 40, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 140, 0, 255);
		}
		else if (nCntTitle == TITLE_MINI)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(350.0f, 380.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(350.0f, 280.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(470.0f, 380.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(470.0f, 280.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 240, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 240, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 240, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 240, 0, 255);
		}
		else if (nCntTitle == TITLE_PUSH)
		{
			// 頂点座標の設定 (XYZ)
			pVtx[0].pos = D3DXVECTOR3(325.0f, 650.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(325.0f, 600.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(925.0f, 650.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(925.0f, 600.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);
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
	g_pVtxBuffTitle->Unlock();

	// タイトル時のサウンド
	PlaySound(SOUND_LABEL_BGM000);	

	return S_OK;
}

//*****************************************************************************************************************
// タイトルの終了処理
//*****************************************************************************************************************
void UninitTitle(void)
{
	
	// 頂点バッファの開放
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		// テクスチャの開放
		if (g_apTexTitle[nCntTitle] != NULL)
		{
			g_apTexTitle[nCntTitle]->Release();
			g_apTexTitle[nCntTitle] = NULL;
		}
	}
}

//*****************************************************************************************************************
//　タイトルの更新処理
//*****************************************************************************************************************
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;

	// エンターキーが押された場合
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		g_bEnter = true;
		StopSound(SOUND_LABEL_BGM000);	// サウンドを止める 
		SetFade(FADE_OUT, MODE_RULE);	// ゲーム画面に飛ぶ＆フェードアウト
	}


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{
		if (nCntTitle == TITLE_TITLE)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(370.0f, 10.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(370.0f, -300.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(870.0f, 10.0f + g_TitleMove * g_CntMove, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(870.0f, -300.0f + g_TitleMove * g_CntMove, 0.0f);

			if (g_TitleMove * g_CntMove <= 400)
			{
				g_CntMove++;
			}
		}
		if (nCntTitle == TITLE_MINI)
		{
			// 頂点情報の設定
			pVtx[0].pos = D3DXVECTOR3(350.0f, 0.0f + g_MiniMove * g_CntMiniMove, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(350.0f, -140.0f + g_MiniMove * g_CntMiniMove, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(470.0f, 0.0f + g_MiniMove * g_CntMiniMove, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(470.0f, -140.0f + g_MiniMove * g_CntMiniMove, 0.0f);


			if (g_MiniMove * g_CntMiniMove <= 400)
			{
				g_CntMiniMove++;
			}
		}

		// プッシュエンターの点滅処理
		if (nCntTitle == TITLE_PUSH)
		{
			g_nCntPush++;

			if (g_nCntPush >= g_nCntEnter)
			{
				if (g_bPush == true)
				{
					// 頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 100, 0, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 100, 0, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

					g_bPush = false;
				}

				else if (g_bPush == false)
				{
					// 頂点カラー
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

					g_bPush = true;
				}
				g_nCntPush = 0;

			}
		}

		// エンター押されたら
		if (g_bEnter == true)
		{
			g_nCntEnter = 12;
		}

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}
//*****************************************************************************************************************
// タイトルの描画処理
//*****************************************************************************************************************
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		// テクスチャの設定
		pDevice->SetTexture(0, g_apTexTitle[nCntTitle]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
	}
}
