//=================================================================================================================
//
// リザルトの処理　〔result.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

//*******************************************************************************************************
// 前方宣言
//*******************************************************************************************************


//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************
#define MAX_RESULT_BG (2)		// 背景の最大数


//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CResult : public CScene
{
public:
	CResult();
	~CResult();
	static CResult *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_RESULT_BG];		// 背景のテクスチャーポインタ
	CScene2D *m_apScene2D[MAX_RESULT_BG];					// ポリゴンのポインタ
	int m_nInterbal;										// 待つ時間
};



//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================

#endif 


