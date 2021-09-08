//======================================================================================================
//
// メイン処理 [scene2D.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "scene.h"

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// 頂点座標、頂点カラー

//*******************************************************************************************************
// 構造体定義
//*******************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 0.1で固定
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CScene2D:public CScene
{
public:
	CScene2D();
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetTexture(int nPatternAnim, int nPatterNum);
	void SetTexture(float TexU, float TexV);
	void Setcol(D3DXCOLOR col);
	D3DXVECTOR3 GetPosition(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9      m_pTexture = NULL;		// テクスチャのポインタ
	D3DXVECTOR3             m_pos;					// ポリゴンの位置
	D3DXCOLOR				m_col;					// カラーの変数
};
#endif
