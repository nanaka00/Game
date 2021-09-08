//======================================================================================================
//
// マネージャー処理 [manager.h]
// Author : nanaka maeno
//
//======================================================================================================

//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "keyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "polygon.h"
#include "life.h"
#include "time.h"
#include "title.h"
#include "game.h"
#include "rule.h"
#include "result.h"
#include "fade.h"

//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CRule *CManager::m_pRule = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;

//======================================================================================================
// コンストラクタ
//======================================================================================================
CManager::CManager()
{
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CManager::~CManager()
{

}
//======================================================================================================
// 初期化処理
//======================================================================================================
HRESULT CManager::Init(HWND hWnd, HINSTANCE hInstance, bool bWindow)
{
	// レンダラーの生成
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	// キーボードの生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// サウンドの生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// フェードの生成
	m_pFade = new CFade;
	m_pFade->Init(m_mode);

	// テクスチャのロード
	CNumber::Load();
	CPolygon::Load();
	CBullet::Load();
	CTitle::Load();
	CRule::Load();
	CResult::Load();


	// モードの呼び出し
	SetMode(m_mode);

	return S_OK;
}

//======================================================================================================
// 終了処理
//======================================================================================================
void CManager::Uninit(void)
{

	// テクスチャのアンロード
	CNumber::Unload();
	CPolygon::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CTitle::Unload();
	CRule::Unload();
	CResult::Unload();


	// サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// キーボードの破棄
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}


	// フェードの破棄
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}	

	// レンダラーの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// すべてのオブジェクトの破棄
	CScene::ReleaseAll();

}

//======================================================================================================
// 更新処理
//======================================================================================================
void CManager::Update(void)
{
	// キーボードの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// レンダラーの更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// オブジェクトの更新処理
	CScene::UpdeteAll();

	// フェードの更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

}

//======================================================================================================
// 描画処理
//======================================================================================================
void CManager::Draw(void)
{
	// レンダラーの描画
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//======================================================================================================
// モードの設定処理
//======================================================================================================
void CManager::SetMode(MODE mode)
{
	//画面遷移の終了処理
	switch (m_mode)
	{// タイトル画面の終了処理
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
		// 説明画面の終了処理
	case MODE_RULE:
		if (m_pRule != NULL)
		{
			m_pRule->Uninit();
			m_pRule = NULL;
		}
		break;
		// ゲーム画面の終了処理
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
		// リザルト画面の終了処理
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	}

	// すべてを破棄
	CScene::ReleaseAll();

	// モードの変更
	m_mode = mode;

	//画面遷移の初期化処理
	switch (m_mode)
	{
	case MODE_TITLE:

		m_pTitle = new CTitle;

		// タイトル画面の初期化処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}

		break;

	case MODE_RULE:

		m_pRule = new CRule;

		// ルール画面の初期化処理
		if (m_pRule != NULL)
		{
			m_pRule->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}

		break;


	case MODE_GAME:
		m_pGame = new CGame;

		// ゲーム画面の初期化処理
		if (m_pGame != NULL)
		{
			m_pGame->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}

		break;

	case MODE_RESULT:

		m_pResult = new CResult;

		// リザルト画面の初期化処理
		if (m_pResult != NULL)
		{
			m_pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}
		break;
	}
}

//======================================================================================================
// レンダラーの取得処理
//======================================================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//======================================================================================================
// キーボードの取得処理
//======================================================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//======================================================================================================
// サウンドの取得処理
//======================================================================================================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}


