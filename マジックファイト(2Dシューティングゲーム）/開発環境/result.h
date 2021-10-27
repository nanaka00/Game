//=================================================================================================================
//
// リザルト画面の処理　〔result.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//=================================================================================================================
// マクロ定義
//=================================================================================================================
#define MAX_RESULT (3)							// タイトル最大数

//=================================================================================================================
// 列挙型 (複数の変数に一連の整数値を付ける必要がある場合に使う）
//=================================================================================================================
// 種類...
typedef enum
{

	RESULT_CLEAR_BG = 0,// クリア画面背景
	RESULT_CLEAR_LOGO,	// ゲームクリアロゴ	
	RESULT_CLEAR_PUSH,	// エンターボタン	
	RESULT_CLEAR_MAX	// 種類の最大値
}RESULT_CLEAR;

typedef enum
{
	RESULT_OVER_BG = 0,	// クリア画面背景
	RESULT_OVER_LOGO,	// ゲームクリアロゴ
	RESULT_OVER_PUSH,	// エンターボタン	
	RESULT_OVER_MAX		// 種類の最大値
}RESULT_OVER;

//=================================================================================================================
// プロトタイプ宣言
//=================================================================================================================
HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetResult(bool bClear);

#endif