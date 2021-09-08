//======================================================================================================
//
// キーボード処理 [keyboard.cpp]
// Author : nanaka maeno
//
//======================================================================================================
#include "input.h"
#include "keyboard.h"

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************

//*******************************************************************************************************
// プロトタイプ宣言
//*******************************************************************************************************


//*******************************************************************************************************
// グローバル変数
//*******************************************************************************************************


//======================================================================================================
// コンストラクタ
//======================================================================================================
CInputKeyboard::CInputKeyboard()
{
}

//======================================================================================================
// デストラクタ
//======================================================================================================
CInputKeyboard::~CInputKeyboard()
{

}

//*****************************************************************************************************************
//	初期化処理
//*****************************************************************************************************************
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// インプットの初期処理
	CInput::Init(hInstance, hWnd);


	//入力デバイス
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットの設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//アクセス権の取得
	m_pDevice->Acquire();
	{
		return S_OK;
	}
}

//*****************************************************************************************************************
//終了処理
//*****************************************************************************************************************
void CInputKeyboard::Uninit(void)
{
}


//*****************************************************************************************************************
//	更新処理
//*****************************************************************************************************************
void CInputKeyboard::Update(void)
{
	//変数宣言
	BYTE aKeyState[NUM_KEY_MAX];	//キーボード現在の入力情報

	//デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < NUM_KEY_MAX; nKey++)
		{
			//トリガー
			m_aKeyStateTrigger[nKey] = (m_aKeyState[nKey] & aKeyState[nKey] ^ aKeyState[nKey]);

			//リリース
			m_aKeyStateRelease[nKey] = (m_aKeyState[nKey] | aKeyState[nKey] ^ aKeyState[nKey]);

			//1フレーム前のキープレス情報保存
			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//アクセス権の取得
		m_pDevice->Acquire();
	}

}

//*****************************************************************************************************************
// キーボード情報取得（プレス）
//*****************************************************************************************************************
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}

//*****************************************************************************************************************
// キーボード情報取得（トリガー）
//*****************************************************************************************************************
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//*****************************************************************************************************************
// キーボード情報取得(リリース）
//*****************************************************************************************************************
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}