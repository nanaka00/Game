//======================================================================================================
//
//	プレイヤー処理 [player.cpp]
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
#include "sound.h"
#include "explosion.h"
#include "life.h"
#include "game.h"

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************

//*******************************************************************************************************
// グローバル変数
//*******************************************************************************************************

//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CLife *CPlayer::m_pLife = NULL;

//======================================================================================================
// コンストラクタ
//======================================================================================================
CPlayer::CPlayer()
{
	// 0クリア
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CPlayer::~CPlayer()
{

}


//======================================================================================================
// プレイヤーの初期化処理
//======================================================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_Scale = scale;	
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 初期化
	CScene2D::Init(pos,scale);

	// ライフの生成
	m_pLife = CLife::Create(D3DXVECTOR3(35.0f, 40.0f, 0.0f), D3DXVECTOR3(40.0f, 30.0f, 0.0f));

	// 引数のポスを初期位置に代入
	m_Initpos = pos;

	return S_OK;

}

//======================================================================================================
// プレイヤーの終了処理
//======================================================================================================
void  CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//======================================================================================================
// プレイヤーの更新処理
//======================================================================================================
void  CPlayer::Update(void)
{	
	// 変数宣言
	D3DXVECTOR3 pos = GetPosition();

	// サウンドの取得処理
	CSound *pSound;
	pSound = CManager::GetSound();

	// スコアの取得処理
	CScore *pScore;
	pScore = CGame::GetScore();

	// キーボードの取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		pos.y -= 3.0f;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		pos.x -= 3.0f;
	}

	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		pos.y += 3.0f;
	}

	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		pos.x += 3.0f;
	}

	if (pos.y - m_Scale.y / 2.0f >= SCREEN_HEIGHT)
	{
		pos.y = 0.0f - m_Scale.y / 2.0f;
	}

	// プレイヤーの設定
	SetPosition(pos, m_Scale);

	// 弾の生成
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		CBullet::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(-15.0f, 0.0f, 0.0f));

		pSound->Play(CSound::SOUND_LABEL_SE_SHOT);	// サウンド
	}
	
	// プレイヤーの当たり判定
	CollisionPlayer(pos, m_Scale);

	//sin(Rot + (D3DPA×三分の一))

	StatePlayer();
}

//======================================================================================================
// プレイヤーの描画処理
//======================================================================================================
void  CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//======================================================================================================
// プレイヤーの生成処理
//======================================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init(pos,scale);

	pPlayer->BindTexture(m_pTexture);

	return pPlayer;
}
//======================================================================================================
// テクスチャの読み込み処理
//======================================================================================================
HRESULT CPlayer::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cyara.png", &m_pTexture);

	return S_OK;

}

//======================================================================================================
// テクスチャの破棄処理
//======================================================================================================
void CPlayer::Unload(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

////======================================================================================================
////	プレイヤー移動の操作
////======================================================================================================
//void CPlayer::ControlPlayer(void)
//{
//	// 変数宣言
//	D3DXVECTOR3 pos = GetPosition();
//
//	// キーボードの取得処理
//	CInputKeyboard *pInputKeyboard;
//	pInputKeyboard = CManager::GetInputKeyboard();
//
//
//	if (pInputKeyboard->GetPress(DIK_W) == true)
//	{
//		pos.y -= 3.0f;
//	}
//
//	if (pInputKeyboard->GetPress(DIK_A) == true)
//	{
//		pos.x -= 3.0f;
//	}
//
//	if (pInputKeyboard->GetPress(DIK_S) == true)
//	{
//		pos.y += 3.0f;
//	}
//
//	if (pInputKeyboard->GetPress(DIK_D) == true)
//	{
//		pos.x += 3.0f;
//	}
//
//	if (pos.y - m_Scale.y / 2.0f >= SCREEN_HEIGHT)
//	{
//		pos.y = 0.0f - m_Scale.y / 2.0f;
//	}
//}
//
//======================================================================================================
// プレイヤーの状態
//======================================================================================================
void  CPlayer::StatePlayer(void)
{
	// 敵からのダメージを受けた時
	if (m_State == PLAYERSTATE_DAMAGE)
	{
		// プレイヤーの設定
		SetPosition(m_Initpos, m_Scale);
		m_State = PLAYERSTATE_NORMAL;
	}
}

//======================================================================================================
// プレイヤーの敵の当たり判定
//======================================================================================================
void CPlayer::CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
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
				if (pos.y - (m_Scale.y / 2.2) <= EnemyPos.y + (EnemyScale.y / 3.5) &&
					pos.y + (m_Scale.y / 2.2) >= EnemyPos.y - (EnemyScale.y / 4) &&
					pos.x + (m_Scale.x / 2.2) >= EnemyPos.x - (EnemyScale.x / 3.5) &&
					pos.x - (m_Scale.x / 2.2) <= EnemyPos.x + (EnemyScale.x / 4))
				{
					//// スコアの加算処理
					//pScore->AddScore(100);

					// 爆破の生成
					CExplosion::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

					// プレイヤーの状態
					m_State = PLAYERSTATE_DAMAGE;

					m_pLife->AddLife(1);


					// 爆破のサウンド
					//pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

					return;
				}
			}
		}
	}
}
