//=================================================================================================================
//
// 背景の処理　〔bg.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "bg.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "renderer.h"

//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CBg::m_pTexture[] = {};

//======================================================================================================
// コンストラクタ
//======================================================================================================
CBg::CBg()
{
	
	// 0クリア
	m_apScene2D[0] = NULL;
	m_apScene2D[1] = NULL;
	m_apScene2D[2] = NULL;

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
		m_fPosTexV[nCnt] = 0;
	}
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CBg::~CBg()
{
}

//======================================================================================================
//　背景の初期化処理
//======================================================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos,D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
	}

	// それぞれのスピードを代入
	m_fSpeed[0] = SPEED_1;	
	m_fSpeed[1] = SPEED_2;
	m_fSpeed[2] = SPEED_3;

	return S_OK;
}

//======================================================================================================
//　背景の終了処理
//======================================================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}

	Release();
}

//======================================================================================================
// 背景の更新処理
//======================================================================================================
void CBg::Update(void)
{
	// キーボードの取得処理
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// すべての背景を動かす処理
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_fPosTexU[nCnt] += m_fSpeed[nCnt];
	}

	// 背景真ん中の移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		m_fPosTexU[2] -= m_fSpeed[2];	
	}

	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->SetTexture(m_fPosTexU[nCnt], m_fPosTexV[nCnt]);
	}
}

//======================================================================================================
// 背景の描画処理
//======================================================================================================
void CBg::Draw(void)
{

}

//======================================================================================================
// 背景の生成処理
//======================================================================================================
CBg *CBg::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CBg *pBg = NULL;
	pBg = new CBg;
	pBg->Init(pos,scale);

	return pBg;
}

//======================================================================================================
// テクスチャの読み込み処理
//======================================================================================================
HRESULT CBg::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\EDGE1.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\dot01.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\dot00.png", &m_pTexture[2]);

	return S_OK;

}

//======================================================================================================
// テクスチャの破棄処理
//======================================================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
