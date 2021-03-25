//=================================================================================================================
//
// キーボードの処理　〔input.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef INPUT_H_
#define INPUT_H_

#include "main.h"

//=================================================================================================================
//プロトタイプ宣言
//=================================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);
void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);

#endif