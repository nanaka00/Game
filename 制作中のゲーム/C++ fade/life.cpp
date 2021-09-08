//======================================================================================================
//
// ライフの処理 [life.cpp]
// Author : nanaka maeno
//
//======================================================================================================


//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "life.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"



//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************

//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************

//======================================================================================================
// コンストラクタ
//======================================================================================================
CLife::CLife()
{

}

//======================================================================================================
// デストラクタ
//======================================================================================================
CLife::~CLife()
{

}

//======================================================================================================
// ライフの初期化処理
//======================================================================================================
HRESULT CLife::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{	
	// ライフの初期化
	m_nLife = MAX_LIFE;

	// a
	m_bUse = true;

	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{	// ポリゴンの生成
		m_apLife[nCnt] = CPolygon::Create(pos, scale);
		pos.x += 65;	// ポリゴンの間隔
	}

	return S_OK;

}

//======================================================================================================
// ライフの終了処理
//======================================================================================================
void  CLife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{

		if (m_apLife[nCnt] != NULL)
		{
			m_apLife[nCnt]->Uninit();
			delete m_apLife[nCnt];
			m_apLife[nCnt] = NULL;
		}
	}

	Release();
}

//======================================================================================================
// ライフの更新処理
//======================================================================================================
void  CLife::Update(void)
{

	if (m_nLife <= 0)
	{
		CManager::SetMode(CManager::MODE_RESULT);	// ゲーム画面に飛ぶ＆フェードアウト
	}

}

//======================================================================================================
// ライフの描画処理
//======================================================================================================
void  CLife::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{

		m_apLife[nCnt]->Draw();
	}

}

//======================================================================================================
// ライフの生成処理
//======================================================================================================
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CLife *pLife = NULL;
	pLife = new CLife;
	pLife->Init(pos, scale);

	return pLife;
}

//======================================================================================================
// ライフの取得処理
//======================================================================================================
int CLife::GetLife(void)
{
	return 0;
}

//======================================================================================================
// ライフの減算
//======================================================================================================
void CLife::AddLife(int nLife)
{
	int nAddLife = 0;

	m_nLife -= nLife;

	if (m_nLife >= 0)
	{
		m_apLife[m_nLife]->SetUse(false);
	}
}
