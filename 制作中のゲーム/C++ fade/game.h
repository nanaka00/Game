//======================================================================================================
//
// �v���C���[���� [player.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "scene2D.h"

//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************

//*******************************************************************************************************
// �O���錾
//*******************************************************************************************************
class CBg;
class CLight;
class CLife;
class CEnemy;
class CPlayer;
class CScore;
class CTime;

//*******************************************************************************************************
// �N���X��`
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
	static CPlayer *m_pPlayer;					// �v���C���[�̃|�C���^
	static CBg *m_pBg;							// �w�i�̃|�C���^
	static CLight *m_pLight;;					// ���C�g�̃|�C���^
	static CEnemy *m_pEnemy;					// �G�̃|�C���^
	static CScore *m_pScore;					// �X�R�A�̃|�C���^
	static CLife *m_pLife;						// ���C�t�̃|�C���^
	static CTime *m_pTime;						// �^�C���̃|�C���^
	int m_nTimeCnt = 0;							// �^�C���̃J�E���^�[


};
#endif 