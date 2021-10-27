//=================================================================================================================
//
// �G�̏����@�kenemy.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//=================================================================================================================
// �}�N����`
//=================================================================================================================
#define MAX_ENEMY (256)										// �G�̍ő吔

//��
#define ENEMY_LIFE_BOB (50)						 			// ��̃��C�t
#define ENEMY_SIZE_BOB (D3DXVECTOR3(50.0f,50.0f,0.0f))		// ��̑傫��
#define ENEMY_MOVE_BOB (D3DXVECTOR3(0.0f,1.0f,0.0f))		// ��̑���
//�ڋ�
#define ENEMY_LIFE_EYE  (50)								// �ڋʂ̃��C�t
#define ENEMY_SIZE_EYE (D3DXVECTOR3(35.0f,45.0f,0.0f))		// �ڋʂ̑傫��
#define ENEMY_MOVE_EYE (D3DXVECTOR3(0.0f,1.2f,0.0f))		// �ڋʂ̑���
//�L
#define ENEMY_LIFE_CAT  (50)								// �L�̃��C�t
#define ENEMY_SIZE_CAT (D3DXVECTOR3(45.0f,45.0f,0.0f))		// �L�̑傫��
#define ENEMY_MOVE_CAT (D3DXVECTOR3(0.0f,1.0f,0.0f))		// �L�̑���

//=================================================================================================================
//	�񋓌^ (�����̕ϐ��Ɉ�A�̐����l��t����K�v������ꍇ�Ɏg���j
//=================================================================================================================

// �G�̎��
typedef enum
{
	ENEMYTYPE_BOB = 0,	// �{�u
	ENEMYTYPE_EYE,		// �ڋ�
	ENEMYTYPE_CAT,		// �L
	ENEMYTYPE_MAX		// ��ނ̍ő�l
}ENEMYTYPE;

// �G�̏��
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
	ENEMYSTATE_MAX
}ENEMYSTATE;

//=================================================================================================================
//	�\����
//=================================================================================================================

// �G�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 size;	// �傫��
	D3DXVECTOR3 move;	// �ړ���
	ENEMYTYPE type;		// ���
	int nLife;			// ���C�t
	bool bUse;			// �g�p���Ă��邩�ǂ���
	ENEMYSTATE state;	// ���
	int nCounterState;	// ��ԃJ�E���^�[
}ENEMY;

//=================================================================================================================
// �v���g�^�C�v�錾
//=================================================================================================================
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, ENEMYTYPE type);
ENEMY *GetEnemy(void);

// �e�ւ̒��_���W�̐ݒ�
void SetVertexEnemy(int nCntEnemy);
bool HitEnemy(int nIdx, int nDamage);
#endif // !_ENEMY_H_

