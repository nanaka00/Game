//======================================================================================================
//
// キーボード処理 [keyboard.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "input.h"


//*******************************************************************************************************
// ライブラリファイルのリンク
//*******************************************************************************************************


//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************
#define NUM_KEY_MAX (256)	//キーの最大数

//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CInputKeyboard:public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

private:
	BYTE m_aKeyState[NUM_KEY_MAX]; 							// キーボードへの入力情報
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];					// キートリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];					// キーリリース情報
	BYTE m_aKeyStateRepeat[NUM_KEY_MAX];					// キーリピート情報
	int m_aCountRepeat[NUM_KEY_MAX];						// キーリピートカウンター

};

#endif