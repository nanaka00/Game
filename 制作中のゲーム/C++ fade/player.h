//======================================================================================================
//
// �v���C���[���� [player.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

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

class CLife;

//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CPlayer:public CScene2D
{
public:
	CPlayer();
	~CPlayer();
	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	void StatePlayer(void);
	void CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 scale);

	void ControlPlayer(void);

	//==================================
	//�񋓌^
	//==================================
	typedef enum
	{
		PLAYERSTATE_NORMAL = 0,	// �ʏ�
		PLAYERSTATE_DAMAGE,		// �_���[�W		
		PLAYERSTATE_DEATH,		// ���S
		PLAYERSTATE_MAX
	}PLAYERSTATE;

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �v���C���[�̃e�N�X�`���[�|�C���^
	D3DXVECTOR3 m_Move;						// �v���C���[�̓�����
	D3DXVECTOR3 m_Scale;					// �v���C���[�̃T�C�Y
	PLAYERSTATE m_State;					// �v���C���[�̏��
	D3DXVECTOR3 m_Initpos;					// �v���C���[�̃T�C�Y
	static CLife *m_pLife;					// �v���C���[���C�t�̃|�C���^
	int Rot;								// �v���C���[�̉�]


};
#endif 