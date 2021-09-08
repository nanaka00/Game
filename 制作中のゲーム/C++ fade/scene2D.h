//======================================================================================================
//
// ���C������ [scene2D.h]
// Author : nanaka maeno
//
//======================================================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "scene.h"

//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************
#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		// ���_���W�A���_�J���[

//*******************************************************************************************************
// �\���̒�`
//*******************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// 0.1�ŌŒ�
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

//*******************************************************************************************************
// �N���X��`
//*******************************************************************************************************
class CScene2D:public CScene
{
public:
	CScene2D();
	~CScene2D();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale);
	void SetTexture(int nPatternAnim, int nPatterNum);
	void SetTexture(float TexU, float TexV);
	void Setcol(D3DXCOLOR col);
	D3DXVECTOR3 GetPosition(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9      m_pTexture = NULL;		// �e�N�X�`���̃|�C���^
	D3DXVECTOR3             m_pos;					// �|���S���̈ʒu
	D3DXCOLOR				m_col;					// �J���[�̕ϐ�
};
#endif
