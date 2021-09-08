//=================================================================================================================
//
// �t�F�[�h�̏����@�kfade.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================


//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "fade.h"
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "polygon.h"
#include "renderer.h"


//*******************************************************************************************************
// �ÓI�����o�ϐ��錾
//*******************************************************************************************************
CFade::FADE CFade::m_fade = FADE_OUT;
CManager::MODE CFade::m_modeNext = CManager::MODE_TITLE;

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CFade::CFade()
{
}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CFade::~CFade()
{

}


//======================================================================================================
// �t�F�[�h�̏���������
//======================================================================================================
HRESULT CFade::Init(CManager::MODE modeNext)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �ϐ��̏�����
	m_fade = CFade::FADE_IN;
	m_modeNext = modeNext;
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);


	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,			// �m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,					// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,	
		&m_pVtxBuffFade,
		NULL)))
	{
		return E_FAIL;
	}

	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;


	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ� (XYZ)
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

	// ���_���̐ݒ�
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
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffFade->Unlock();

	return S_OK;

}

//======================================================================================================
// �t�F�[�h�̏I������
//======================================================================================================
void  CFade::Uninit(void)
{	
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//======================================================================================================
// �t�F�[�h�̍X�V����
//======================================================================================================
void  CFade::Update(void)
{
	// �\���̂̃|�C���^�ϐ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);



	// �����x��1����
	// �t�F�[�h�C��		
	if (m_fade == FADE_IN)
	{	// ���l�ɓ���̐�����
		m_colorFade.a -= 0.01f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;


		if (m_colorFade.a <= 0.0f)
		{
			m_fade = FADE_NONE;
		}
	}

	// �t�F�[�h�A�E�g
	else if (m_fade == FADE_OUT)
	{	// ���l�ɓ���̐�����
		m_colorFade.a += 0.01f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = m_colorFade;
		pVtx[1].col = m_colorFade;
		pVtx[2].col = m_colorFade;
		pVtx[3].col = m_colorFade;

		if (m_colorFade.a >= 1.0f)
		{
			m_fade = FADE_IN;			
			CManager::SetMode(m_modeNext);	// ���[�h�̊֐�
		}
	}

	else if(m_fade == FADE_NONE)
	{
		// �����Ȃ���
		m_colorFade.a = 0.0f;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuffFade->Unlock();

}

//======================================================================================================
// �t�F�[�h�̕`�揈��
//======================================================================================================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݗ�
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//======================================================================================================
// �t�F�[�h�̐�������
//======================================================================================================
CFade *CFade::Create(CManager::MODE modeNext)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		pFade = new CFade;

		if (pFade != NULL)
		{
			pFade->Init(modeNext);
		}
	}
	return pFade;
}

//======================================================================================================
// �t�F�[�h�̐ݒ菈��
//======================================================================================================
void CFade::SetFade(FADE fade,CManager::MODE modeNext)
{
	m_fade = fade;
	m_modeNext = modeNext;
}

//======================================================================================================
// �t�F�[�h�̎擾����
//======================================================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}