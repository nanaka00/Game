//=================================================================================================================
//
// キーボードの処理　〔input.cpp〕
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "input.h"

//=================================================================================================================
//	マクロ定義
//=================================================================================================================
#define NUM_KEY_MAX (256)	//キーの最大数

//=================================================================================================================
//グローバル変数（cpp内で共通でも一つ一つの値）
//=================================================================================================================
LPDIRECTINPUT8 g_pInput = NULL;							//DirectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;				//入力デバイス（キーボード）へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX]; 							//キーボードへの入力情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];					//キートリガー情報
BYTE g_aKeyStateRelease[NUM_KEY_MAX];					//キーリリース情報
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];					//キーリピート情報
int g_aCountRepeat[NUM_KEY_MAX];						//キーリピートカウンター


//*****************************************************************************************************************
//	初期化処理
//*****************************************************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevkeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(g_pDevkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//アクセス権の取得
	g_pDevkeyboard->Acquire();
	{
		return S_OK;
	}
}

//*****************************************************************************************************************
//終了処理
//*****************************************************************************************************************
void UninitKeyboard(void)
{
	//入力デバイス（キーボード）の開放
	if (g_pDevkeyboard != NULL)
	{
		//アクセス権の破棄
		g_pDevkeyboard->Unacquire();
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}

	//Directinputオブジェクトの開放
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//*****************************************************************************************************************
//	更新処理
//*****************************************************************************************************************
void UpdateKeyboard(void)
{
	//変数宣言
	BYTE aKeyState[NUM_KEY_MAX];	//キーボード現在の入力情報

	//デバイスからデータを取得
	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < NUM_KEY_MAX; nKey++)
		{
			//トリガー
			g_aKeyStateTrigger[nKey] = (g_aKeyState[nKey] & aKeyState[nKey] ^ aKeyState[nKey] );

			//リリース
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey] | aKeyState[nKey] ^ aKeyState[nKey]);

			//1フレーム前のキープレス情報保存
			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//アクセス権の取得
		g_pDevkeyboard->Acquire();
	}
}


//*****************************************************************************************************************
//キーボード情報取得（プレス）
//*****************************************************************************************************************
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) ? true : false;
}
//*****************************************************************************************************************
//キーボード情報取得（トリガー）
//*****************************************************************************************************************
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//*****************************************************************************************************************
//キーボード情報取得(リリース）
//*****************************************************************************************************************
bool GetKeyboardRelease(int nKey)
{
	return(g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}