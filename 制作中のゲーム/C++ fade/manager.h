//======================================================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"

//*******************************************************************************************************
// �O���錾
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
// �}�N����`
//*******************************************************************************************************

//*******************************************************************************************************
// �\���̒�`
//*******************************************************************************************************

//*******************************************************************************************************
// �N���X��`
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
	static CRenderer *m_pRenderer;				// �����_���[�̃|�C���^
	static CInputKeyboard *m_pInputKeyboard;	// ���͂̃|�C���^
	static CTitle *m_pTitle;					// �^�C�g���̃|�C���^
	static CSound *m_pSound;					// �T�E���h�̃|�C���^
	static CRule *m_pRule;						// ���[���̃|�C���^
	static CGame *m_pGame;						// �Q�[���̃|�C���^�[
	static CResult *m_pResult;					// ���U���g�̃|�C���^
	static CFade *m_pFade;						// �t�F�[�h�̃|�C���^
	static MODE m_mode;							// ���[�h�̕ϐ�

};
#endif 