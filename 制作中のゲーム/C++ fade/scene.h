//======================================================================================================
//
// ���C������ [scene.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"

//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************
#define MAX_SCENE (128)	// �V�[���̍ő吔


//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CScene
{
public:

	//*************************
	// �I�u�W�F�N�g�̎��
	//*************************
	typedef enum 
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,		// �v���C���[
		OBJTYPE_ENEMY,		// �G
		OBJTYPE_BULLET,		// �e
		OBJTYPE_LIFE,		// ���C�t
		OBJTYPE_MAX,		
	}OBJTYPE;

	CScene();
	virtual ~CScene();
	void SetObjType(OBJTYPE objType);
	OBJTYPE GetObjType(void);
	static CScene *GetScene(int nCntScene);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetScale(void);
	void SetPosition(D3DXVECTOR3 pos);
	void SetScale(D3DXVECTOR3 scale);

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	static void ReleaseAll(void);
	static void UpdeteAll(void);
	static void DrawAll(void);

protected:
	void Release(void);

private:
	static CScene *m_apScene[MAX_SCENE];	// �V�[���̃C���X�^���X����
	static int		m_nNumAll;				// �I�u�W�F�N�g�̑���
	int				m_nID;					// �i�[��̔ԍ�
	OBJTYPE			m_objType;				// �I�u�W�F�N�g�̎��
	D3DXVECTOR3     m_Pos;					// �ʒu
	D3DXVECTOR3     m_Scale;				// �傫��

};
#endif