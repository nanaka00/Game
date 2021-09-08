//=================================================================================================================
//
// タイトルの処理　〔title.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "manager.h"
#include "scene2D.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "renderer.h"
#include "title.h"
#include "rule.h"
#include "fade.h"

//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[] = {};

//======================================================================================================
// コンストラクタ
//======================================================================================================
CTitle::CTitle()
{
	// 0クリア
	m_apScene2D[TITLE_BG] = NULL;
	m_apScene2D[TITLE_DOT1] = NULL;
	m_apScene2D[TITLE_DOT2] = NULL;
	m_apScene2D[TITLE_ENTER] = NULL;

	// ボタンの色の初期化
	m_ButtonCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
		m_fPosTexV[nCnt] = 0;
	}
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CTitle::~CTitle()
{
}

//======================================================================================================
// タイトルの初期化処理
//======================================================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
	}

	// ボタンの色の初期化
	m_ButtonCol = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// それぞれのスピードを代入
	m_fSpeed[0] = TITLE_SPEED_1;
	m_fSpeed[1] = TITLE_SPEED_2;
	m_fSpeed[2] = TITLE_SPEED_3;

	return S_OK;
}

//======================================================================================================
// タイトルの終了処理
//======================================================================================================
void CTitle::Uninit(void)
{
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
	}

	Release();
}

//======================================================================================================
// タイトルの更新処理
//======================================================================================================
void CTitle::Update(void)
{
	// キーボードの取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_fPosTexV[1] -= m_fSpeed[1];
	m_fPosTexV[2] -= m_fSpeed[2];

	EnterUI();

	for (int nCnt = 0; nCnt <TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt]->SetTexture(m_fPosTexU[nCnt], m_fPosTexV[nCnt]);
	}
	

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{		
		CManager::GetFade()->SetFade(CFade::FADE_OUT,CManager::MODE_RULE);
	}

}

//======================================================================================================
// タイトルの描画処理
//======================================================================================================
void CTitle::Draw(void)
{

}

//======================================================================================================
// タイトルの生成処理
//======================================================================================================
CTitle *CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle;
	pTitle->Init(pos, scale);

	return pTitle;
}

//======================================================================================================
// テクスチャの読み込み処理
//======================================================================================================
HRESULT CTitle::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG013.PNG", &m_pTexture[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\dot01.png", &m_pTexture[TITLE_DOT1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\dot00.png", &m_pTexture[TITLE_DOT2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER02.png", &m_pTexture[TITLE_ENTER]);

	return S_OK;

}

//======================================================================================================
// テクスチャの破棄処理
//======================================================================================================
void CTitle::Unload(void)
{
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//======================================================================================================
// エンターボタンの処理処理
//======================================================================================================
void CTitle::EnterUI(void)
{
	m_apScene2D[TITLE_ENTER]->Setcol(m_ButtonCol);

	m_ButtonCol.a += AddCol;	// α値の減算加算

	if (m_ButtonCol.a >= 1.0f)
	{
		AddCol = -0.04f;
	}

	if (m_ButtonCol.a <= 0.0f)
	{
		AddCol = 0.04f;
	}

}
