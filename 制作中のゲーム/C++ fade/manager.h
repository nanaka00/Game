//======================================================================================================
//
// マネージャー処理 [manager.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*******************************************************************************************************
// ヘッダファイルのインクルード
//*******************************************************************************************************
#include "main.h"

//*******************************************************************************************************
// 前方宣言
//*******************************************************************************************************
class CRenderer;
class CInputKeyboard;
class CSound;
class CPlayer;
class CBg;
class CEnemy;
class CScore;
class CLife;
class CTitle;
class CGame;
class CRule;
class CResult;
class CFade;

//*******************************************************************************************************
// マクロ定義
//*******************************************************************************************************

//*******************************************************************************************************
// 構造体定義
//*******************************************************************************************************

//*******************************************************************************************************
// クラス定義
//*******************************************************************************************************
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_RULE,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	}MODE;

	CManager();
	~CManager();
	HRESULT Init(HWND hWnd, HINSTANCE hInstance, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);
	static MODE GetMode(void) { return m_mode; }
	static CRenderer *GetRenderer(void);
	static CInputKeyboard *GetInputKeyboard(void);
	static CSound *GetSound(void);
	static CFade *GetFade(void) { return m_pFade; };

private:
	static CRenderer *m_pRenderer;				// レンダラーのポインタ
	static CInputKeyboard *m_pInputKeyboard;	// 入力のポインタ
	static CTitle *m_pTitle;					// タイトルのポインタ
	static CSound *m_pSound;					// サウンドのポインタ
	static CRule *m_pRule;						// ルールのポインタ
	static CGame *m_pGame;						// ゲームのポインター
	static CResult *m_pResult;					// リザルトのポインタ
	static CFade *m_pFade;						// フェードのポインタ
	static MODE m_mode;							// モードの変数

};
#endif 