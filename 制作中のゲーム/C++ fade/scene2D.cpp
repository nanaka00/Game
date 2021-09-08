//======================================================================================================
//
//	シーン処理 [scene.cpp]
// Author : nanaka maeno
//
//======================================================================================================


//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "keyboard.h"
#include "player.h"

//======================================================================================================
// コンストラクタ
//======================================================================================================
CScene2D::CScene2D()
{

}

//======================================================================================================
// デストラクタ
//======================================================================================================
CScene2D::~CScene2D()
{

}


//======================================================================================================
// ポリゴンの初期化処理
//======================================================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_2D *pVtx;

	// 引数を代入
	m_pos = pos;

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y - scale.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y - scale.y / 2, 0.0f);

	// テクスチャー情報
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

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

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;


}

//======================================================================================================
// ポリゴンの終了処理
//======================================================================================================
void  CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();	// m_系、関数すべてを破棄

}

//======================================================================================================
// ポリゴンの更新処理
//======================================================================================================
void  CScene2D::Update(void)
{

}

//======================================================================================================
// ポリゴンの描画処理
//======================================================================================================
void  CScene2D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


//======================================================================================================
// 生成処理
//======================================================================================================
CScene2D* CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// インスタンス生成
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->Init(pos,scale);
	}
	return pScene2D;
}

//======================================================================================================
// 位置の設定
//======================================================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	VERTEX_2D *pVtx;

	// 設定処理
	CScene::SetPosition(pos);
	CScene::SetScale(scale);

	m_pos = pos;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y - scale.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y - scale.y / 2, 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//======================================================================================================
// 位置の取得処理
//======================================================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//======================================================================================================
// テクスチャの割り当て処理
//======================================================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//======================================================================================================
// 位置の設定
//======================================================================================================
void CScene2D::SetTexture(int nPatternAnim,int nPatterNum)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ情報
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + 0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + 0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + (1.0f / nPatterNum), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + (1.0f / nPatterNum), 0.0f);

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//======================================================================================================
// 背景のテクスチャの設定
//======================================================================================================
void CScene2D::SetTexture(float TexU,float TexV)
{
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ情報
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexU, 1.0f + TexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + TexU, 0.0f + TexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + TexU, 1.0f + TexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + TexU, 0.0f + TexV);
								  
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//======================================================================================================
// カラーの設定
//======================================================================================================
void CScene2D::Setcol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	m_col = col;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ情報
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
