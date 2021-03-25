//=================================================================================================================
//
// ポーズの処理　〔pause.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//=================================================================================================================
//プロトタイプ宣言
//=================================================================================================================
typedef enum 
{
	PAUSE_MENE_CONTINOE = 1,	//コンテニュー
	PAUSE_MENE_RETRY,			//リトライ
	PAUSE_MENE_QUIT,			//終了
	PAUSE_MENE_POINT,			//ポイント
	PAUSE_MENE_MAX
}PAUSE_MENE_;

//=================================================================================================================
//プロトタイプ宣言
//=================================================================================================================
HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

#endif