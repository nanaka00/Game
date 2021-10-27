//=================================================================================================================
//
// 弾の処理　〔bullet.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "bullet.h"	// インクルードファイル
#include "enemy.h"
#include "explosion.h"
#include "sound.h"
#include "Score.h"
#include "player.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================
#define MAX_BULLET (256)


//=================================================================================================================
//	弾の構造体
//=================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 size;	// 大きさ
	D3DXVECTOR3 move;	// 移動量
	int nLife;			// 寿命
	bool bUse;			// 使用しているかどうか
	BULLETTYRE type;	// 種類
}BULLET;


//=================================================================================================================
//	グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;				// 弾のテクスチャー情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		// 弾のバッファ情報
BULLET g_aBullet[MAX_BULLET];							// 弾の情報
 

//*****************************************************************************************************************
//	弾の初期化処理
//*****************************************************************************************************************
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bulled-light-yellow.png", &g_pTextureBullet);
	
	// グローバル変数の初期化（弾の情報の初期化)
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 0;
		g_aBullet[nCntBullet].bUse = false;
	}

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		// 頂点座標の設定 (XYZ)
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// rhwの設定（（（（（（（2Dでしか使わない））））））
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラー
		pVtx[0].col = D3DCOLOR_RGBA(250, 0, 250, 255);
		pVtx[1].col = D3DCOLOR_RGBA(250, 0, 250, 255);
		pVtx[2].col = D3DCOLOR_RGBA(250, 0, 250, 255);
		pVtx[3].col = D3DCOLOR_RGBA(250, 0, 250, 255);

		// 頂点情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//	弾の終了処理
//*****************************************************************************************************************
void UninitBullet(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}

	// テクスチャの開放
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}


//*****************************************************************************************************************
//	弾の更新処理
//*****************************************************************************************************************
void UpdateBullet(void)
{
	// 変数宣言
	BULLET *pBullet;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pBullet = &g_aBullet[0];
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++, pVtx += 4)
	{
		// 使用しているなら
		if (pBullet->bUse == true)
		{
			// 位置の更新
			pBullet->pos += pBullet->move;

			if (pBullet->type == BULLETTYRE_PLAYER)
			{ // 敵との当たり判定
				// 敵を取得
				pEnemy = GetEnemy();

				for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					// 敵が使われているなら
					if (pEnemy->bUse == true)
					{
						// 当たり判定の計算
						if (pBullet->pos.y - (pBullet->size.y / 2) <= pEnemy->pos.y + (pEnemy->size.y / 2) &&
							pBullet->pos.y + (pBullet->size.y / 2) >= pEnemy->pos.y - (pEnemy->size.y / 2) &&
							pBullet->pos.x + (pBullet->size.x / 2) >= pEnemy->pos.x - (pEnemy->size.x / 2) &&
							pBullet->pos.x - (pBullet->size.x / 2) <= pEnemy->pos.x + (pEnemy->size.x / 2))
						{
							// ダメージ量
							HitEnemy(nCntEnemy, 10);

							// ヒットしたときのサウンド
							PlaySound(SOUND_LABEL_SE_HIT);

							// 未使用にする
							pBullet->bUse = false;
						}
					}
				}
			}
			// 敵の弾
			else if (pBullet->type == BULLETTYRE_ENEMY)
			{// プレイヤーとの当たり判定

				// デバイスの取得
				pPlayer = GetPlayer();

				if (pBullet->pos.y - (pBullet->size.y / 2) <= pPlayer->pos.y + (pPlayer->size.y / 2) &&
					pBullet->pos.y + (pBullet->size.y / 2) >= pPlayer->pos.y - (pPlayer->size.y / 2) &&
					pBullet->pos.x + (pBullet->size.x / 2) >= pPlayer->pos.x - (pPlayer->size.x / 2) &&
					pBullet->pos.x - (pBullet->size.x / 2) <= pPlayer->pos.x + (pPlayer->size.x / 2))
				{
					// ダメージ量
					HitPlayer(10);

					// ヒットしたときのサウンド
					PlaySound(SOUND_LABEL_SE_HIT);

					// 未使用にする
					pBullet->bUse = false;
				}
			}
		}

		// 頂点座標の設定 (XYZ)
		SetVertexBullet(nCntBullet);

		// 1フレームごとにライフを減らす
		pBullet->nLife--;

		// 弾の寿命チェック
		if (pBullet->nLife <= 0)
		{
			// 未使用にする
			pBullet->bUse = false;
		}
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//*****************************************************************************************************************
//	弾の描画処理
//*****************************************************************************************************************
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBullet);

  	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);	//
		}
	}
}
//*****************************************************************************************************************
//	弾の設定
//*****************************************************************************************************************
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 move, int nLife, BULLETTYRE type)
{
	// 変数宣言
	VERTEX_2D *pVtx;		// 関数化しているから今は使っていない
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		// もし
		if (pBullet->bUse == false)
		{
			pBullet->pos = pos;
			pBullet->size = size;

			// 頂点座標の設定
			SetVertexBullet(nCntBullet);

			// 引数をむすびつける
			pBullet->move = move;
			pBullet->bUse = true;
			pBullet->nLife = nLife;
			pBullet->type = type;
			break;
		}
		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//*****************************************************************************************************************
//	弾の頂点座標の設定
//*****************************************************************************************************************
void SetVertexBullet(int nCntBullet)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	// pVtxを合わせる
	pVtx += 4 * nCntBullet;

	// 頂点情報の設定(Nの順番）
	pVtx[0].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(-(g_aBullet[nCntBullet].size.x / 2), +(g_aBullet[nCntBullet].size.y / 2), 0.0f);
	pVtx[1].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(-(g_aBullet[nCntBullet].size.x / 2), -(g_aBullet[nCntBullet].size.y / 2), 0.0f);
	pVtx[2].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(+(g_aBullet[nCntBullet].size.x / 2), +(g_aBullet[nCntBullet].size.y / 2), 0.0f);
	pVtx[3].pos = g_aBullet[nCntBullet].pos + D3DXVECTOR3(+(g_aBullet[nCntBullet].size.x / 2), -(g_aBullet[nCntBullet].size.y / 2), 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}
