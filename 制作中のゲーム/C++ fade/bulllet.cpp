//======================================================================================================
//
//	弾の処理 [bullet.cpp]
// Author : nanaka maeno
//
//======================================================================================================


//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "main.h"
#include "player.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "keyboard.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "score.h"
#include "game.h"


//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************


//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CBullet::m_pTexture = NULL;

//======================================================================================================
// コンストラクタ
//======================================================================================================
CBullet::CBullet()
{
	// 0クリア
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CBullet::~CBullet()
{

}


//======================================================================================================
// 弾の初期化処理
//======================================================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	// 初期化
	m_Scale = scale;
	m_Move = move;
	m_nLife = BULLET_LIFE;

	CScene2D::Init(pos, scale);

	return S_OK;

}

//======================================================================================================
// 弾の終了処理
//======================================================================================================
void  CBullet::Uninit(void)
{
	CScene2D::Uninit();
}

//======================================================================================================
// 弾の更新処理
//======================================================================================================
void  CBullet::Update(void)
{	
	// サウンドの取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// スコアの取得処理
	CScore *pScore;
	pScore = CGame::GetScore();

	// ライフを１づつ減らす
	m_nLife--;

	// 位置の取得
	D3DXVECTOR3 pos = GetPosition();

	// 移動量を位置に反映
	pos -= m_Move;

	// 位置の設定
	SetPosition(pos, m_Scale);

	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		// シーンの取得処理
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();
			
			if (objType == OBJTYPE_ENEMY)
			{
				D3DXVECTOR3 EnemyPos = pScene->GetPosition();
				D3DXVECTOR3 EnemyScale = pScene->GetScale();

				// 当たり判定の計算
				if (pos.y - (m_Scale.y / 2) <= EnemyPos.y + (EnemyScale.y / 3.5) &&
					pos.y + (m_Scale.y / 2) >= EnemyPos.y - (EnemyScale.y / 3.5) &&
					pos.x + (m_Scale.x / 2) >= EnemyPos.x - (EnemyScale.x / 3.5) &&
					pos.x - (m_Scale.x / 2) <= EnemyPos.x + (EnemyScale.x / 3.5))
				{
					// スコアの加算処理
					pScore->AddScore(100);

					// 爆破の生成
					CExplosion::Create(EnemyPos, D3DXVECTOR3(45.0f, 45.0f, 0.0f));	// 敵が死んだときの爆破処理

					// 爆破のサウンド
					pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

					// 敵の破棄
					pScene->Uninit();

					// 弾の破棄
					Uninit();

					return;
				}
			}
		}
	}

	if (m_nLife < 0)
	{
		// 爆破の生成
		CExplosion::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

		// 爆破のサウンド
		pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

		Uninit();

		return;
	}

	// 画面外に出たら消す
	if (pos.y + m_Scale.y / 2.0f < 0.0f || pos.y - m_Scale.y / 2.0f > SCREEN_HEIGHT ||
		pos.x - m_Scale.x / 2.0f > SCREEN_WIDTH || pos.x + m_Scale.x / 2.0f < 0.0f)
	{
		Uninit();

		return;
	}	
}

//======================================================================================================
// 弾の描画処理
//======================================================================================================
void  CBullet::Draw(void)
{
	CScene2D::Draw();
}

//======================================================================================================
// 弾の生成処理
//======================================================================================================
CBullet *CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 move)
{
	CBullet *pBullet = NULL;
	pBullet = new CBullet;
	pBullet->Init(pos, scale,move);
	pBullet->BindTexture(m_pTexture);


	return pBullet;
}

//======================================================================================================
// テクスチャの読み込み処理
//======================================================================================================
HRESULT CBullet::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\スマイル.png", &m_pTexture);

	return S_OK;
}

//======================================================================================================
// テクスチャの破棄処理
//======================================================================================================
void CBullet::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
