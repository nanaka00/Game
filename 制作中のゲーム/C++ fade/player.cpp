//======================================================================================================
//
//	�v���C���[���� [player.cpp]
// Author : nanaka maeno
//
//======================================================================================================


//*******************************************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*******************************************************************************************************
#include "main.h"
#include "player.h"
#include "scene.h"
#include "renderer.h"
#include "scene2D.h"
#include "manager.h"
#include "keyboard.h"
#include "bullet.h"
#include "sound.h"
#include "explosion.h"
#include "life.h"
#include "game.h"

//*******************************************************************************************************
// �}�N����`
//*******************************************************************************************************

//*******************************************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************************************

//*******************************************************************************************************
// �ÓI�����o�ϐ��錾
//*******************************************************************************************************
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture = NULL;
CLife *CPlayer::m_pLife = NULL;

//======================================================================================================
// �R���X�g���N�^
//======================================================================================================
CPlayer::CPlayer()
{
	// 0�N���A
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//======================================================================================================
// �f�X�g���N�^
//======================================================================================================
CPlayer::~CPlayer()
{

}


//======================================================================================================
// �v���C���[�̏���������
//======================================================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	m_Scale = scale;	
	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ������
	CScene2D::Init(pos,scale);

	// ���C�t�̐���
	m_pLife = CLife::Create(D3DXVECTOR3(35.0f, 40.0f, 0.0f), D3DXVECTOR3(40.0f, 30.0f, 0.0f));

	// �����̃|�X�������ʒu�ɑ��
	m_Initpos = pos;

	return S_OK;

}

//======================================================================================================
// �v���C���[�̏I������
//======================================================================================================
void  CPlayer::Uninit(void)
{
	CScene2D::Uninit();
}

//======================================================================================================
// �v���C���[�̍X�V����
//======================================================================================================
void  CPlayer::Update(void)
{	
	// �ϐ��錾
	D3DXVECTOR3 pos = GetPosition();

	// �T�E���h�̎擾����
	CSound *pSound;
	pSound = CManager::GetSound();

	// �X�R�A�̎擾����
	CScore *pScore;
	pScore = CGame::GetScore();

	// �L�[�{�[�h�̎擾����
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		pos.y -= 3.0f;
	}

	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		pos.x -= 3.0f;
	}

	if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		pos.y += 3.0f;
	}

	if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		pos.x += 3.0f;
	}

	if (pos.y - m_Scale.y / 2.0f >= SCREEN_HEIGHT)
	{
		pos.y = 0.0f - m_Scale.y / 2.0f;
	}

	// �v���C���[�̐ݒ�
	SetPosition(pos, m_Scale);

	// �e�̐���
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true)
	{
		CBullet::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f), D3DXVECTOR3(-15.0f, 0.0f, 0.0f));

		pSound->Play(CSound::SOUND_LABEL_SE_SHOT);	// �T�E���h
	}
	
	// �v���C���[�̓����蔻��
	CollisionPlayer(pos, m_Scale);

	//sin(Rot + (D3DPA�~�O���̈�))

	StatePlayer();
}

//======================================================================================================
// �v���C���[�̕`�揈��
//======================================================================================================
void  CPlayer::Draw(void)
{
	CScene2D::Draw();
}

//======================================================================================================
// �v���C���[�̐�������
//======================================================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	CPlayer *pPlayer = NULL;
	pPlayer = new CPlayer;
	pPlayer->Init(pos,scale);

	pPlayer->BindTexture(m_pTexture);

	return pPlayer;
}
//======================================================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//======================================================================================================
HRESULT CPlayer::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cyara.png", &m_pTexture);

	return S_OK;

}

//======================================================================================================
// �e�N�X�`���̔j������
//======================================================================================================
void CPlayer::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

////======================================================================================================
////	�v���C���[�ړ��̑���
////======================================================================================================
//void CPlayer::ControlPlayer(void)
//{
//	// �ϐ��錾
//	D3DXVECTOR3 pos = GetPosition();
//
//	// �L�[�{�[�h�̎擾����
//	CInputKeyboard *pInputKeyboard;
//	pInputKeyboard = CManager::GetInputKeyboard();
//
//
//	if (pInputKeyboard->GetPress(DIK_W) == true)
//	{
//		pos.y -= 3.0f;
//	}
//
//	if (pInputKeyboard->GetPress(DIK_A) == true)
//	{
//		pos.x -= 3.0f;
//	}
//
//	if (pInputKeyboard->GetPress(DIK_S) == true)
//	{
//		pos.y += 3.0f;
//	}
//
//	if (pInputKeyboard->GetPress(DIK_D) == true)
//	{
//		pos.x += 3.0f;
//	}
//
//	if (pos.y - m_Scale.y / 2.0f >= SCREEN_HEIGHT)
//	{
//		pos.y = 0.0f - m_Scale.y / 2.0f;
//	}
//}
//
//======================================================================================================
// �v���C���[�̏��
//======================================================================================================
void  CPlayer::StatePlayer(void)
{
	// �G����̃_���[�W���󂯂���
	if (m_State == PLAYERSTATE_DAMAGE)
	{
		// �v���C���[�̐ݒ�
		SetPosition(m_Initpos, m_Scale);
		m_State = PLAYERSTATE_NORMAL;
	}
}

//======================================================================================================
// �v���C���[�̓G�̓����蔻��
//======================================================================================================
void CPlayer::CollisionPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{
	for (int nCntScene = 0; nCntScene < MAX_SCENE; nCntScene++)
	{
		// �V�[���̎擾����
		CScene *pScene;
		pScene = CScene::GetScene(nCntScene);

		if (pScene != NULL)
		{
			CScene::OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_ENEMY)
			{
				D3DXVECTOR3 EnemyPos = pScene->GetPosition();
				D3DXVECTOR3 EnemyScale = pScene->GetScale();

				// �����蔻��̌v�Z
				if (pos.y - (m_Scale.y / 2.2) <= EnemyPos.y + (EnemyScale.y / 3.5) &&
					pos.y + (m_Scale.y / 2.2) >= EnemyPos.y - (EnemyScale.y / 4) &&
					pos.x + (m_Scale.x / 2.2) >= EnemyPos.x - (EnemyScale.x / 3.5) &&
					pos.x - (m_Scale.x / 2.2) <= EnemyPos.x + (EnemyScale.x / 4))
				{
					//// �X�R�A�̉��Z����
					//pScore->AddScore(100);

					// ���j�̐���
					CExplosion::Create(pos, D3DXVECTOR3(50.0f, 50.0f, 0.0f));

					// �v���C���[�̏��
					m_State = PLAYERSTATE_DAMAGE;

					m_pLife->AddLife(1);


					// ���j�̃T�E���h
					//pSound->Play(CSound::SOUND_LABEL_SE_EXPLOSION);

					return;
				}
			}
		}
	}
}
