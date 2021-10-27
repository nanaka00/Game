//=================================================================================================================
//
// 敵の処理　〔enemy.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================
#define MAX_ENEMY (256)										// 敵の最大数

//手
#define ENEMY_LIFE_BOB (50)						 			// 手のライフ
#define ENEMY_SIZE_BOB (D3DXVECTOR3(50.0f,50.0f,0.0f))		// 手の大きさ
#define ENEMY_MOVE_BOB (D3DXVECTOR3(0.0f,1.0f,0.0f))		// 手の速さ
//目玉
#define ENEMY_LIFE_EYE  (50)								// 目玉のライフ
#define ENEMY_SIZE_EYE (D3DXVECTOR3(35.0f,45.0f,0.0f))		// 目玉の大きさ
#define ENEMY_MOVE_EYE (D3DXVECTOR3(0.0f,1.2f,0.0f))		// 目玉の速さ
//猫
#define ENEMY_LIFE_CAT  (50)								// 猫のライフ
#define ENEMY_SIZE_CAT (D3DXVECTOR3(45.0f,45.0f,0.0f))		// 猫の大きさ
#define ENEMY_MOVE_CAT (D3DXVECTOR3(0.0f,1.0f,0.0f))		// 猫の速さ

//=================================================================================================================
//	列挙型 (複数の変数に一連の整数値を付ける必要がある場合に使う）
//=================================================================================================================

// 敵の種類
typedef enum
{
	ENEMYTYPE_BOB = 0,	// ボブ
	ENEMYTYPE_EYE,		// 目玉
	ENEMYTYPE_CAT,		// 猫
	ENEMYTYPE_MAX		// 種類の最大値
}ENEMYTYPE;

// 敵の状態
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

//=================================================================================================================
//	構造体
//=================================================================================================================

// 敵の構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 size;	// 大きさ
	D3DXVECTOR3 move;	// 移動量
	ENEMYTYPE type;		// 種類
	int nLife;			// ライフ
	bool bUse;			// 使用しているかどうか
	ENEMYSTATE state;	// 状態
	int nCounterState;	// 状態カウンター
}ENEMY;

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type);
ENEMY *GetEnemy(void);

// 弾への頂点座標の設定
void SetVertexEnemy(int nCntEnemy);
bool HitEnemy(int nIdx, int nDamage);
#endif // !_ENEMY_H_

