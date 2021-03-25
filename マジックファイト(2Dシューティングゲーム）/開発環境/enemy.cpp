//=================================================================================================================
//
// 敵の処理　〔enemy.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "enemy.h"
#include "explosion.h"
#include "Score.h"
#include "sound.h"
#include "bullet.h"
#include "player.h"
#include <time.h>
#include <cmath>

//=================================================================================================================
//	マクロ定義		(cpp内でしか使わないマクロはcppに、ｈには、ほかにも使うものを入れる）
//=================================================================================================================


//=================================================================================================================
//	グローバル変数（cpp内で共通でも一つ一つの値）
//================================================================================================================
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMYTYPE_MAX] = {};	//テクスチャーへの配列のポインター
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//頂点バッファへのポインター
ENEMY g_aEnemy[MAX_ENEMY];									//敵の情報
int g_TimeCnt;

//*****************************************************************************************************************
// 敵の初期化処理
//*****************************************************************************************************************
HRESULT InitEnemy(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	srand((unsigned int)time(0));
	g_TimeCnt = 0;
	//デバイスの取得
	pDevice = GetDevice();

//===================
//テクスチャの読み込み
//===================
	//ボブ
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE3.png", &g_apTextureEnemy[ENEMYTYPE_BOB]);

	//目玉
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE1.png", &g_apTextureEnemy[ENEMYTYPE_EYE]);

	//猫
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE2.png", &g_apTextureEnemy[ENEMYTYPE_CAT]);


	//グローバル変数の初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy,
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{

		//頂点座標の設定 (XYZ)
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();

	return S_OK;

	//変数＝atan2f(//敵のX－プレイヤーのX、敵のY－プレイヤーのY)//敵とプレイヤーの角度
		//D3DXVECTOR3（sinf(D3DX_PI+変数)*スピード,cosf(D3DX_PI-変数)*スピード,0.0f)←これをムーブに入れる

}

//*****************************************************************************************************************
// 敵の終了処理
//*****************************************************************************************************************
void UninitEnemy(void)
{
	//頂点バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}

	for (int nCntTex = 0; nCntTex < ENEMYTYPE_MAX; nCntTex++)
	{
		//テクスチャの開放
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
}

//*****************************************************************************************************************
//　敵の更新処理
//*****************************************************************************************************************
void UpdateEnemy(void)
{
	//変数宣言
	ENEMY *pEnemy;			//敵のポインタ
	pEnemy = &g_aEnemy[0];	//敵のポインタに敵の配列を入れる
	VERTEX_2D *pVtx;
	g_TimeCnt++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		//使用しているなら
		if (pEnemy->bUse == true)
		{
			//位置の更新
			pEnemy->pos += pEnemy->move;

			//頂点座標の設定 (XYZ)
			SetVertexEnemy(nCntEnemy);

			//敵の弾
			if (rand() % 300 == 0)
			{
				SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y + (60 / 4.0f), 0.0f),
					BULLET_PLAYER_SIZE, D3DXVECTOR3(-5.0f, 5.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_ENEMY);
				SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y + (60 / 4.0f), 0.0f),
					BULLET_PLAYER_SIZE, D3DXVECTOR3(5.0f, 5.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_ENEMY);
				//変数＝atan2f(//敵のX－プレイヤーのX、敵のY－プレイヤーのY)//敵とプレイヤーの角度
				//D3DXVECTOR3（sinf(D3DX_PI+変数)*スピード,cosf(D3DX_PI-変数)*スピード,0.0f)←これをムーブに入れる

			}

			//寿命チェック
			if (pEnemy->nLife <= 0)
			{
				//未使用にする
				pEnemy->bUse = false;
			}

			//画面外チェック
		}

		//敵の状態
		switch (g_aEnemy[nCntEnemy].state)
		{
		case ENEMYSTATE_DAMAGE:
			g_aEnemy[nCntEnemy].nCounterState--;
			if (g_aEnemy[nCntEnemy].nCounterState <= 0)		//ダメージを受けたあと通常になる
			{
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

				//頂点カラー
				pVtx[0 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3 + 4 * nCntEnemy].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			break;
		}

	}

	//後で関数分けする敵のランダム出現
	if (g_TimeCnt % 200 == 0)
	{
		int nPosH = rand() % 350 + 50; //100-400 ->200-800
		int nPosE = rand() % 350 + 450; //100-200 ->300-600
		int nPosC = rand() % 350 + 850; //100-300 ->500->1500
		int nType = rand() % 3;
		switch (nType)
		{
		case 0:
			SetEnemy(D3DXVECTOR3((float)nPosH, 0.0f, 0.0f), ENEMYTYPE_BOB);			//手の配置

			SetEnemy(D3DXVECTOR3((float)nPosE, 0.0f, 0.0f), ENEMYTYPE_EYE);			//目玉の配置

			SetEnemy(D3DXVECTOR3((float)nPosC, 0.0f, 0.0f), ENEMYTYPE_CAT);			//猫の配置
			break;
		case 1:
			SetEnemy(D3DXVECTOR3((float)nPosH, 0.0f, 0.0f), ENEMYTYPE_EYE);			//手の配置

			SetEnemy(D3DXVECTOR3((float)nPosE, 0.0f, 0.0f), ENEMYTYPE_CAT);			//目玉の配置

			SetEnemy(D3DXVECTOR3((float)nPosC, 0.0f, 0.0f), ENEMYTYPE_BOB);			//猫の配置
			break;
		case 2:
			SetEnemy(D3DXVECTOR3((float)nPosH, 0.0f, 0.0f), ENEMYTYPE_CAT);			//手の配置

			SetEnemy(D3DXVECTOR3((float)nPosE, 0.0f, 0.0f), ENEMYTYPE_BOB);			//目玉の配置

			SetEnemy(D3DXVECTOR3((float)nPosC, 0.0f, 0.0f), ENEMYTYPE_EYE);			//猫の配置
			break;
		default:
			break;
		}

	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//*****************************************************************************************************************
// 敵の描画処理
//*****************************************************************************************************************
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		//もし使われているなら
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntEnemy, 2);	
																			
		}
	}
}

//*****************************************************************************************************************
// 敵の設定処理
//*****************************************************************************************************************
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type)
{
	VERTEX_2D *pVtx;	//関数化しているから今は使っていない
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];


	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//引数を結びつける
			pEnemy->pos = pos;		//posをpEnemy->posに入れる
			pEnemy->type = type;	//typeをpEnemy->typeに入れる

			//頂点座標の設定
			SetVertexEnemy(nCntEnemy);

			//初期化
			pEnemy->move = D3DXVECTOR3(0,0,0);
			pEnemy->bUse = true;

			//種類ごとの不変の値を結びつける
			switch (pEnemy->type)
			{
			case ENEMYTYPE_BOB:		//ザリガニの設定
				pEnemy->nLife = ENEMY_LIFE_BOB;
				pEnemy->size = ENEMY_SIZE_BOB;
				pEnemy->move = ENEMY_MOVE_BOB;
				break;

			case ENEMYTYPE_EYE:
				pEnemy->nLife = ENEMY_LIFE_EYE;
				pEnemy->size = ENEMY_SIZE_EYE;
				pEnemy->move = ENEMY_MOVE_EYE;
				break;

			case ENEMYTYPE_CAT:
				pEnemy->nLife = ENEMY_LIFE_CAT;
				pEnemy->size = ENEMY_SIZE_CAT;
				pEnemy->move = ENEMY_MOVE_CAT;
				break;
			}
			break;	//forを抜けるため
		}
		pVtx += 4;	//ポインタを進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//*****************************************************************************************************************
// 敵の取得処理
//*****************************************************************************************************************
ENEMY *GetEnemy(void)
{
	//配列の最初からポインタで渡す
	return &g_aEnemy[0];
}

//*****************************************************************************************************************
//	敵の頂点座標の設定
//*****************************************************************************************************************
void SetVertexEnemy(int nCntEnemy)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4 * nCntEnemy;		

	//頂点情報の設定(Nの順番）(Enemy）
	pVtx[0].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(-(g_aEnemy[nCntEnemy].size.x / 2), +(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);
	pVtx[1].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(-(g_aEnemy[nCntEnemy].size.x / 2), -(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);
	pVtx[2].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(+(g_aEnemy[nCntEnemy].size.x / 2), +(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);
	pVtx[3].pos = g_aEnemy[nCntEnemy].pos + D3DXVECTOR3(+(g_aEnemy[nCntEnemy].size.x / 2), -(g_aEnemy[nCntEnemy].size.y / 2), 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}

//*****************************************************************************************************************
//	敵の当たり判定
//*****************************************************************************************************************
bool HitEnemy(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;

	//敵にダメージを与えたとき何点入れるか
	AddScore(100);

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	g_aEnemy[nIdx].nLife -= nDamage;
	if (g_aEnemy[nIdx].nLife <= 0)		//ライフが0になったら使われていない処理
	{
		g_aEnemy[nIdx].bUse = false;
		
		//敵を倒した時に何点入れるか
		switch (g_aEnemy[nIdx].type)
		{
		case ENEMYTYPE_BOB:
			AddScore(500);
			break;

		case ENEMYTYPE_EYE:
			AddScore(500);
			break;

		case ENEMYTYPE_CAT:
			AddScore(700);
			break;

		default:
			break;
		}
		
		//爆発とそのサウンド
		SetExplosion(g_aEnemy[nIdx].pos, g_aEnemy[nIdx].size);
		PlaySound(SOUND_LABEL_SE_EXPLOSION);

		return true;
	}
	else
	{
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 5;

		//頂点カラー
		pVtx[0 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		pVtx[1 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		pVtx[2 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		pVtx[3 + 4 * nIdx].col = D3DCOLOR_RGBA(240, 0, 240, 150);
		
		return false;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}