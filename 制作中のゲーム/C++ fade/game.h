//======================================================================================================
//
// プレイヤー処理 [player.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "scene2D.h"

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************

//*******************************************************************************************************
// 前方宣言
//*******************************************************************************************************
class CBg;
class CLight;
class CLife;
class CEnemy;
class CPlayer;
class CScore;
class CTime;

//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CGame: public CScene
{
public:
	CGame();
	~CGame();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//static void LoadAll(void);
	//static void UnloadAll(void);

	static CBg *GetBg(void);
	static CLight *GetLight(void);
	static CEnemy *GetEnemy(void);
	static CScore *GetScore(void);
	static CTime *GetTime(void);
	static CLife *GetLife(void);
	static CPlayer *GetPlayer(void);
	
private:
	static CPlayer *m_pPlayer;					// プレイヤーのポインタ
	static CBg *m_pBg;							// 背景のポインタ
	static CLight *m_pLight;;					// ライトのポインタ
	static CEnemy *m_pEnemy;					// 敵のポインタ
	static CScore *m_pScore;					// スコアのポインタ
	static CLife *m_pLife;						// ライフのポインタ
	static CTime *m_pTime;						// タイムのポインタ
	int m_nTimeCnt = 0;							// タイムのカウンター


};
#endif 