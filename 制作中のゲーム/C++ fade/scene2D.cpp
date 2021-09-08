//======================================================================================================
//
//	�V�[������ [scene.cpp]
// Author : nanaka maeno
//
//======================================================================================================


//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "keyboard.h"
#include "player.h"

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CScene2D::CScene2D()
{

}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CScene2D::~CScene2D()
{

}


//======================================================================================================
// �|���S���̏���������
//======================================================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	VERTEX_2D *pVtx;

	// ��������
	m_pos = pos;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y - scale.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y - scale.y / 2, 0.0f);

	// �e�N�X�`���[���
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// rhw�̐ݒ�i�i�i�i�i�i�i2D�ł����g��Ȃ��j�j�j�j�j�j
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;


}

//======================================================================================================
// �|���S���̏I������
//======================================================================================================
void  CScene2D::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();	// m_�n�A�֐����ׂĂ�j��

}

//======================================================================================================
// �|���S���̍X�V����
//======================================================================================================
void  CScene2D::Update(void)
{

}

//======================================================================================================
// �|���S���̕`�揈��
//======================================================================================================
void  CScene2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

}


//======================================================================================================
// ��������
//======================================================================================================
CScene2D* CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	// �C���X�^���X����
	CScene2D *pScene2D;
	pScene2D = new CScene2D;

	if (pScene2D != NULL)
	{
		pScene2D->Init(pos,scale);
	}
	return pScene2D;
}

//======================================================================================================
// �ʒu�̐ݒ�
//======================================================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	VERTEX_2D *pVtx;

	// �ݒ菈��
	CScene::SetPosition(pos);
	CScene::SetScale(scale);

	m_pos = pos;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - scale.x / 2, m_pos.y - scale.y / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y + scale.y / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + scale.x / 2, m_pos.y - scale.y / 2, 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//======================================================================================================
// �ʒu�̎擾����
//======================================================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}

//======================================================================================================
// �e�N�X�`���̊��蓖�ď���
//======================================================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//======================================================================================================
// �ʒu�̐ݒ�
//======================================================================================================
void CScene2D::SetTexture(int nPatternAnim,int nPatterNum)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����
	pVtx[0].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + 0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + 0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + (1.0f / nPatterNum), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPatternAnim * (1.0f / nPatterNum) + (1.0f / nPatterNum), 0.0f);

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}

//======================================================================================================
// �w�i�̃e�N�X�`���̐ݒ�
//======================================================================================================
void CScene2D::SetTexture(float TexU,float TexV)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����
	pVtx[0].tex = D3DXVECTOR2(0.0f + TexU, 1.0f + TexV);
	pVtx[1].tex = D3DXVECTOR2(0.0f + TexU, 0.0f + TexV);
	pVtx[2].tex = D3DXVECTOR2(1.0f + TexU, 1.0f + TexV);
	pVtx[3].tex = D3DXVECTOR2(1.0f + TexU, 0.0f + TexV);
								  
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//======================================================================================================
// �J���[�̐ݒ�
//======================================================================================================
void CScene2D::Setcol(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;
	m_col = col;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
