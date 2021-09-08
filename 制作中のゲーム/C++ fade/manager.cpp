//======================================================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : nanaka maeno
//
//======================================================================================================

//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "keyboard.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "enemy.h"
#include "score.h"
#include "polygon.h"
#include "life.h"
#include "time.h"
#include "title.h"
#include "game.h"
#include "rule.h"
#include "result.h"
#include "fade.h"

//*******************************************************************************************************
// �ÓI�����o�ϐ��錾
//*******************************************************************************************************
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CRule *CManager::m_pRule = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_mode = MODE_TITLE;

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CManager::CManager()
{
}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CManager::~CManager()
{

}
//======================================================================================================
// ����������
//======================================================================================================
HRESULT CManager::Init(HWND hWnd, HINSTANCE hInstance, bool bWindow)
{
	// �����_���[�̐���
	m_pRenderer = new CRenderer;
	m_pRenderer->Init(hWnd, bWindow);

	// �L�[�{�[�h�̐���
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	// �T�E���h�̐���
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	// �t�F�[�h�̐���
	m_pFade = new CFade;
	m_pFade->Init(m_mode);

	// �e�N�X�`���̃��[�h
	CNumber::Load();
	CPolygon::Load();
	CBullet::Load();
	CTitle::Load();
	CRule::Load();
	CResult::Load();


	// ���[�h�̌Ăяo��
	SetMode(m_mode);

	return S_OK;
}

//======================================================================================================
// �I������
//======================================================================================================
void CManager::Uninit(void)
{

	// �e�N�X�`���̃A�����[�h
	CNumber::Unload();
	CPolygon::Unload();
	CExplosion::Unload();
	CBullet::Unload();
	CTitle::Unload();
	CRule::Unload();
	CResult::Unload();


	// �T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Uninit();
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}


	// �t�F�[�h�̔j��
	if (m_pFade != NULL)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}	

	// �����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();

		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// ���ׂẴI�u�W�F�N�g�̔j��
	CScene::ReleaseAll();

}

//======================================================================================================
// �X�V����
//======================================================================================================
void CManager::Update(void)
{
	// �L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	// �����_���[�̍X�V����
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// �I�u�W�F�N�g�̍X�V����
	CScene::UpdeteAll();

	// �t�F�[�h�̍X�V����
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

}

//======================================================================================================
// �`�揈��
//======================================================================================================
void CManager::Draw(void)
{
	// �����_���[�̕`��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//======================================================================================================
// ���[�h�̐ݒ菈��
//======================================================================================================
void CManager::SetMode(MODE mode)
{
	//��ʑJ�ڂ̏I������
	switch (m_mode)
	{// �^�C�g����ʂ̏I������
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			m_pTitle = NULL;
		}
		break;
		// ������ʂ̏I������
	case MODE_RULE:
		if (m_pRule != NULL)
		{
			m_pRule->Uninit();
			m_pRule = NULL;
		}
		break;
		// �Q�[����ʂ̏I������
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;
		// ���U���g��ʂ̏I������
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			m_pResult = NULL;
		}
		break;
	}

	// ���ׂĂ�j��
	CScene::ReleaseAll();

	// ���[�h�̕ύX
	m_mode = mode;

	//��ʑJ�ڂ̏���������
	switch (m_mode)
	{
	case MODE_TITLE:

		m_pTitle = new CTitle;

		// �^�C�g����ʂ̏���������
		if (m_pTitle != NULL)
		{
			m_pTitle->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}

		break;

	case MODE_RULE:

		m_pRule = new CRule;

		// ���[����ʂ̏���������
		if (m_pRule != NULL)
		{
			m_pRule->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}

		break;


	case MODE_GAME:
		m_pGame = new CGame;

		// �Q�[����ʂ̏���������
		if (m_pGame != NULL)
		{
			m_pGame->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}

		break;

	case MODE_RESULT:

		m_pResult = new CResult;

		// ���U���g��ʂ̏���������
		if (m_pResult != NULL)
		{
			m_pResult->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
		}
		break;
	}
}

//======================================================================================================
// �����_���[�̎擾����
//======================================================================================================
CRenderer* CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//======================================================================================================
// �L�[�{�[�h�̎擾����
//======================================================================================================
CInputKeyboard* CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//======================================================================================================
// �T�E���h�̎擾����
//======================================================================================================
CSound* CManager::GetSound(void)
{
	return m_pSound;
}


