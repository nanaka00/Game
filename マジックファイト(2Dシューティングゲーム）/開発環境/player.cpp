//=================================================================================================================
//
// プレイヤーの処理　〔player.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "player.h"	// インクルードファイル
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "enemy.h"
#include "explosion.h"
#include "light.h"
#include "fade.h"
#include"result.h"

//=================================================================================================================
//	マクロ定義
//=================================================================================================================
#define PLAYER_SPEED (7.0f)	// プレイヤー移動の速さ
#define PLAYER_SIZE (60.0f)	// プレイヤーのサイズ

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			// テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// 頂点バッファのポインタ
PLAYER g_Player;

//*****************************************************************************************************************
//	プレイヤーの初期化処理
//*****************************************************************************************************************
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	// デバイスの取得
	pDevice = GetDevice();

	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPlayer,
		NULL)))
	{
		return E_FAIL;
	}

	// プレイヤーのライフ
	g_Player.nLife = PLAYER_LIFE;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\chara.png", &g_pTexturePlayer);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	// テクスチャ情報の設定
	pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

	// rhwの設定（（（（（（（2Dでしか使わない））））））
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// 初期値設定
	g_Player.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 3.5 / 4), 0.0f);
	 
	// 頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//*****************************************************************************************************************
//　プレイヤーの終了処理
//*****************************************************************************************************************
void UninitPlayer(void)
{
	// 頂点バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	// テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//*****************************************************************************************************************
//　プレイヤーの更新処理
//*****************************************************************************************************************

void UpdatePlayer(void)
{
	// 変数宣言
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;		// プレイヤーのポインタ
	ENEMY *pEnemy;			// 敵のポインタ
	

	// 種類ごとの不変の値を結びつける
	g_Player.size = PLAYER_SIZE2;
	
	// プレイヤーの移動
	ControlPlayer();

	// Spaceキーが押された場合
	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		// 弾の発射(サウンド）
		PlaySound(SOUND_LABEL_SE_SHOT);

		// 弾の発射位置の設定
		// 正面
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y + (PLAYER_SIZE / 4.0f), 0.0f),
			BULLET_PLAYER_SIZE, D3DXVECTOR3(0.0f, -15.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_PLAYER);

		// 右斜め
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE / 4.0f), 0.0f),
			BULLET_PLAYER_SIZE, D3DXVECTOR3(5.0f, -10.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_PLAYER);

		// 左斜め
		SetBullet(D3DXVECTOR3(g_Player.pos.x, g_Player.pos.y - (PLAYER_SIZE / 4.0f), 0.0f),
			BULLET_PLAYER_SIZE, D3DXVECTOR3(-5.0f, -10.0f, 0.0f), BULLET_PLAYER_LIFE, BULLETTYRE_PLAYER);
	}
	
	// 画面外制御の関数（頂点情報の設定よりも上でする）
	StayPlayer();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// プレイヤーの状態
	if (g_Player.state == PLAYERSTATE_DAMAGE)
	{
		g_Player.nCounterstate--;
		
		if (g_Player.nCounterstate % 4 < 2)
		{
			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else if (g_Player.nCounterstate % 4 >= 2)
		{
			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 120);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 120);
		}

		if (g_Player.nCounterstate < 0)
		{
			// 頂点カラー
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			
			g_Player.nCounterstate = PLAYERSTATE_NORMAL;
		}
	}

	// 頂点情報の設定(Nの順番）(Player)
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE / 2), g_Player.pos.y + (PLAYER_SIZE / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - (PLAYER_SIZE / 2), g_Player.pos.y - (PLAYER_SIZE / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE / 2), g_Player.pos.y + (PLAYER_SIZE / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + (PLAYER_SIZE / 2), g_Player.pos.y - (PLAYER_SIZE / 2), 0.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
	
	pPlayer = GetPlayer();
	pEnemy = GetEnemy();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			// 敵とプレイヤーの当たり判定
			if (pEnemy->pos.y - (pEnemy->size.y / 2) <= pPlayer->pos.y + (pPlayer->size.y / 2) &&
				pEnemy->pos.y + (pEnemy->size.y / 2) >= pPlayer->pos.y - (pPlayer->size.y / 2) &&
				pEnemy->pos.x + (pEnemy->size.x / 2) >= pPlayer->pos.x - (pPlayer->size.x / 2) &&
				pEnemy->pos.x - (pEnemy->size.x / 2) <= pPlayer->pos.x + (pPlayer->size.x / 2))
			{
				// ヒットしたときのサウンド
				PlaySound(SOUND_LABEL_SE_HIT);

				HitPlayer(10);
			}
		}
	}
}		

//*****************************************************************************************************************
//　プレイヤーの描画処理
//*****************************************************************************************************************
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//*****************************************************************************************************************
//	プレイヤー移動の操作
//*****************************************************************************************************************
void ControlPlayer(void)
{
	if (GetKeyboardPress(DIK_L) == false)
	{
		// キーボード入力
		// 右（D)に押されたとき
		if (GetKeyboardPress(DIK_D) == true)
		{
			// DとWが押された場合
			if (GetKeyboardPress(DIK_W) == true)
			{
				g_Player.pos.x += sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y -= cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}
			// DとSが押された場合
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_Player.pos.x += sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y += cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}
			else
			{
				g_Player.pos.x += PLAYER_SPEED;
			}
		}

		// 左（A）が押された場合
		else if (GetKeyboardPress(DIK_A) == true)
		{	// AとWが同時に押された場合
			if (GetKeyboardPress(DIK_W) == true)
			{
				// 斜め移動の計算
				g_Player.pos.x -= sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y -= cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}

			// AとSが同時に押された場合ww
			else if (GetKeyboardPress(DIK_S) == true)
			{
				g_Player.pos.x -= sinf(D3DX_PI / 4) * PLAYER_SPEED;
				g_Player.pos.y += cosf(D3DX_PI / 4) * PLAYER_SPEED;
			}
			else
			{
				g_Player.pos.x -= PLAYER_SPEED;
			}
		}

		// 下（ｓ）が押された場合
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_Player.pos.y += PLAYER_SPEED;
		}
		// 上（w）が押された場合
		else if (GetKeyboardPress(DIK_W) == true)
		{
			g_Player.pos.y -= PLAYER_SPEED;
		}
	}
}

//*****************************************************************************************************************
//	画面外制御（頂点情報の設定よりも上でする）
//*****************************************************************************************************************
void StayPlayer(void)
{
	// 画面の右端よりプレイヤーの右端が出た時
	if (g_Player.pos.x + (PLAYER_SIZE / 2) > SCREEN_WIDTH-150)
	{
		// 右端でプレイヤーを止める
		g_Player.pos.x = SCREEN_WIDTH-150 - (PLAYER_SIZE / 2);
	}

	// 画面の下端よりプレイヤーの下端が出た時
	if (g_Player.pos.y + (PLAYER_SIZE / 2) > SCREEN_HEIGHT)
	{
		g_Player.pos.y = SCREEN_HEIGHT - (PLAYER_SIZE / 2);
	}

	// 画面の左端よりプレイヤーの左端が出た時
	if (g_Player.pos.x - (PLAYER_SIZE / 2) < 100)
	{
		g_Player.pos.x = 100 + (PLAYER_SIZE / 2);
	}

	// 画面の上端よりプレイヤーの上端が出た時
	if (g_Player.pos.y - (PLAYER_SIZE / 2) <  100)
	{
		g_Player.pos.y = 100 + (PLAYER_SIZE / 2);
	}
}

//*****************************************************************************************************************
// プレイヤーの取得処理
//*****************************************************************************************************************
PLAYER *GetPlayer(void)
{
	// ポインタを返す
	return &g_Player;
}

//*****************************************************************************************************************
// プレイヤーの当たり判定
//*****************************************************************************************************************
bool HitPlayer(int nDamage)
{
	g_Player.nLife -= nDamage;		// プレイヤーのライフから敵の弾のダメージを引く
	if (g_Player.nLife <= 0)		// ライフが0になったら
	{
		g_Player.state = PLAYERSTATE_DEATH;
		SetExplosion(g_Player.pos, g_Player.size);	// 爆発
		PlaySound(SOUND_LABEL_SE_EXPLOSION);		// 爆破サウンド
		StopSound(SOUND_LABEL_BGM001);				// サウンドを止める
		SetResult(false);							// ゲームオーバーに飛ぶ
		SetFade(FADE_OUT, MODE_RESULT);				// フェードアウトをしてリザルト画面に飛ぶ

		return true;
	}
	else
	{
		g_Player.pos = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT * 3.5 / 4), 0.0f);	// 初期位置に戻す

		g_Player.state = PLAYERSTATE_DAMAGE;
		g_Player.nCounterstate= 120;

		return false;
	}
}

