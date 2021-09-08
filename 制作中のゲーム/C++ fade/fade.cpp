//=================================================================================================================
//
// フェードの処理　〔fade.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================


//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "fade.h"
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "polygon.h"
#include "renderer.h"


//*******************************************************************************************************
// 静的メンバ変数宣言
//*******************************************************************************************************
CFade::FADE CFade::m_fade = FADE_OUT;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;

//======================================================================================================
// コンストラクタ
//======================================================================================================
CFade::CFade()
{
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CFade::~CFade()
{

}


//======================================================================================================
// フェードの初期化処理
//======================================================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 変数の初期化
	m_fade = CFade::FADE_IN;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,			// 確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// 頂点フォーマット
		D3DPOOL_MANAGED,	
		&m_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}

	// 構造体のポインタ変数
	VERTEX_2D *pVtx;


	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定 (XYZ)
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	// 頂点情報の設定
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
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// 頂点バッファをアンロックする
	m_pVtxBuffFade->Unlock();

	return S_OK;

}

//======================================================================================================
// フェードの終了処理
//======================================================================================================
void  CFade::Uninit(void)
{	
	// 頂点バッファの破棄
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//======================================================================================================
// フェードの更新処理
//======================================================================================================
void  CFade::Update(void)
{
	// 構造体のポインタ変数
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);



	// 透明度を1から
	// フェードイン		
	if (m_fade == FADE_IN)
	{	// α値に特定の数を代入
		m_colorFade.a -= 0.01f;

		//頂点カラーの設定・赤・緑・青
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;


		if (m_colorFade.a <= 0.0f)
		{
			m_fade = FADE_NONE;
		}
	}

	// フェードアウト
	else if (m_fade == FADE_OUT)
	{	// α値に特定の数を代入
		m_colorFade.a += 0.01f;

		//頂点カラーの設定・赤・緑・青
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		if (m_colorFade.a >= 1.0f)
		{
			m_fade = FADE_IN;			
			CManager::SetMode(m_modeNext);	// モードの関数
		}
	}

	else if(m_fade == FADE_NONE)
	{
		// 何もない時
		m_colorFade.a = 0.0f;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuffFade->Unlock();

}

//======================================================================================================
// フェードの描画処理
//======================================================================================================
void CFade::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設立
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// ポリゴンの描画
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//======================================================================================================
// フェードの生成処理
//======================================================================================================
CFade *CFade::Create(CManager::MODE modeNext)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;

		if (pFade != NULL)
		{
			pFade->Init(modeNext);
		}
	}
	return pFade;
}

//======================================================================================================
// フェードの設定処理
//======================================================================================================
void CFade::SetFade(FADE fade,CManager::MODE modeNext)
{
	m_fade = fade;
	m_modeNext = modeNext;
}

//======================================================================================================
// フェードの取得処理
//======================================================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}