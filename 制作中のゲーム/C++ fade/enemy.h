//======================================================================================================
//
// 敵の処理 [enemy.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "scene2D.h"

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************
#define MAX_ENEMY (3)	// 敵の最大数


//*******************************************************************************************************
// 構造体定義
//*******************************************************************************************************

//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CEnemy : public CScene2D
{
public:
	// 列挙型
	typedef enum
	{
		ENEMY_JELLYFISH = 0,
		ENEMY_SHARK,
		ENEMY_HERMITCRAB,
		ENEMY_MAX
	}ENEMY;

	CEnemy();
	~CEnemy();
	static CEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale,ENEMY type);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	D3DXVECTOR3 Move(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY type);
	void SetType(ENEMY type) { m_Type = type; }
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_ENEMY];	// 敵のテクスチャのポインタ
	D3DXVECTOR3 m_Move;									// 敵の動く量
	D3DXVECTOR3 m_Scale;								// 敵のサイズ
	ENEMY m_Type;										// 敵のタイプ

};

#endif