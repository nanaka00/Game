//=================================================================================================================
//
// �^�C�g���̏����@�ktitle.cpp�l
// Anthor:Nanaka maeno
//
//=================================================================================================================
#include "manager.h"
#include "scene2D.h"
#include "scene.h"
#include "input.h"
#include "keyboard.h"
#include "renderer.h"
#include "title.h"
#include "rule.h"
#include "fade.h"

//*******************************************************************************************************
// �ÓI�����o�ϐ��錾
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CTitle::m_pTexture[] = {};

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CTitle::CTitle()
{
	// 0�N���A
	m_apScene2D[TITLE_BG] = NULL;
	m_apScene2D[TITLE_DOT1] = NULL;
	m_apScene2D[TITLE_DOT2] = NULL;
	m_apScene2D[TITLE_ENTER] = NULL;

	// �{�^���̐F�̏�����
	m_ButtonCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_fSpeed[nCnt] = 0;
		m_fPosTexU[nCnt] = 0;
		m_fPosTexV[nCnt] = 0;
	}
}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CTitle::~CTitle()
{
}

//======================================================================================================
// �^�C�g���̏���������
//======================================================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = new CScene2D;
		m_apScene2D[nCnt]->Init(pos, scale);
		m_apScene2D[nCnt]->BindTexture(m_pTexture[nCnt]);
	}

	// �{�^���̐F�̏�����
	m_ButtonCol = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);

	// ���ꂼ��̃X�s�[�h����
	m_fSpeed[0] = TITLE_SPEED_1;
	m_fSpeed[1] = TITLE_SPEED_2;
	m_fSpeed[2] = TITLE_SPEED_3;

	return S_OK;
}

//======================================================================================================
// �^�C�g���̏I������
//======================================================================================================
void CTitle::Uninit(void)
{
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
	}

	Release();
}

//======================================================================================================
// �^�C�g���̍X�V����
//======================================================================================================
void CTitle::Update(void)
{
	// �L�[�{�[�h�̎擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	m_fPosTexV[1] -= m_fSpeed[1];
	m_fPosTexV[2] -= m_fSpeed[2];

	EnterUI();

	for (int nCnt = 0; nCnt <TITLE_MAX; nCnt++)
	{
		m_apScene2D[nCnt]->SetTexture(m_fPosTexU[nCnt], m_fPosTexV[nCnt]);
	}
	

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{		
		CManager::GetFade()->SetFade(CFade::FADE_OUT,CManager::MODE_RULE);
	}

}

//======================================================================================================
// �^�C�g���̕`�揈��
//======================================================================================================
void CTitle::Draw(void)
{

}

//======================================================================================================
// �^�C�g���̐�������
//======================================================================================================
CTitle *CTitle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CTitle *pTitle = NULL;
	pTitle = new CTitle;
	pTitle->Init(pos, scale);

	return pTitle;
}

//======================================================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//======================================================================================================
HRESULT CTitle::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BG013.PNG", &m_pTexture[TITLE_BG]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\dot01.png", &m_pTexture[TITLE_DOT1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\dot00.png", &m_pTexture[TITLE_DOT2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\PRESS ENTER02.png", &m_pTexture[TITLE_ENTER]);

	return S_OK;

}

//======================================================================================================
// �e�N�X�`���̔j������
//======================================================================================================
void CTitle::Unload(void)
{
	for (int nCnt = 0; nCnt < TITLE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//======================================================================================================
// �G���^�[�{�^���̏�������
//======================================================================================================
void CTitle::EnterUI(void)
{
	m_apScene2D[TITLE_ENTER]->Setcol(m_ButtonCol);

	m_ButtonCol.a += AddCol;	// ���l�̌��Z���Z

	if (m_ButtonCol.a >= 1.0f)
	{
		AddCol = -0.04f;
	}

	if (m_ButtonCol.a <= 0.0f)
	{
		AddCol = 0.04f;
	}

}
